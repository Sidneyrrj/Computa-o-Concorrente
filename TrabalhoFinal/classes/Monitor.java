import java.io.IOException;

public class Monitor {
	private int tarefas_acessadas;
	private int tarefas_disponiveis;
	private int max_requisicoes;
	private int n_tarefas;//total de tarefas que serao realizadas
	private int n_andares;
	private int posicao = 0;// posicao da menor distancia
	private int[] tempInt;
	private int[][] matriz_tarefas;
	private String[] strTarefas;
	
	
	/* o construtor recebe da Main o numero maximo de requisicoes que cada tarefa podera ter, o numero de andares e o 
	numero total de tarefas	que serao passadas para as threads elevadores.*/
	public Monitor(int R, int N, int n_tarefas) {
		this.n_tarefas = n_tarefas;
		this.max_requisicoes = R;
		this.n_andares = N;
		this.strTarefas = new String[n_tarefas];
		this.matriz_tarefas = new int[n_tarefas][3 + max_requisicoes];
	}
	
	
	/* recebe como entrada o objeto da classe que escreve em um arquivo de saida(classe EscreveNoArquivo), o andar atual do
	 elevador, o id da tarefa, o andar de partida da tarefa, o sentido da tarefa e o array de inteiros contendo a tarefa.
	 Esse metodo simplesmente escreve no arquivo de saida, correspondente ao elevador, cada linha com o
	 estado atual do elevador na forma como foi pedido na descrição do trabalho.*/
	public void escreveArquivo(EscreveNoArquivo escreveNoArquivo, int andar_atual, int id_tarefa, int andar_tarefa, int sentido, int[] lista) throws IOException {
		escreveNoArquivo.escreve(andar_atual + "(");
		escreveNoArquivo.escreve(id_tarefa + ", ");
		escreveNoArquivo.escreve(andar_tarefa + ", ");
		escreveNoArquivo.escreve(sentido + ", (");

		for (int i = 0; i < lista.length; i++) {
			if (i == lista.length - 1)
				escreveNoArquivo.escreve(lista[i] + "");
			else
				escreveNoArquivo.escreve(lista[i] + ", ");
		}
		escreveNoArquivo.escreve("))\n");
	}

	
	/* recebe como entrada um array de String(contendo apenas numeros em cada posicao) e retorna um array
	 de inteiros com os numeros correspondentes.*/
	public int[] strToInt(String[] str) {
		int[] lista = new int[str.length];
		for (int i = 0; i < str.length; i++) {
			lista[i] = Integer.parseInt(str[i]);
		}
		return lista;
	}

	/*recebe como entrada a tarefa na forma de String ainda, e a variavel posicao, que eh 
	aonde a tarefa deve ser guardada na matriz_tarefas(variável compartilhada entre as threads dentro do monitor).
	Esse método separa a String tarefa pelo caractere espaço, chama strToInt() e já salva na 
	matriz de tarefas a tarefa na posição correspondente.*/
	public void splitTarefa(String tarefa, int posicao){
		String[] str = tarefa.split(" ");
		tempInt = strToInt(str);
		matriz_tarefas[posicao] = tempInt;
	}
	
	/*recebe como entrada a tarefa na forma de String e a posicao em que devera ser inserida na matriz
	 de tarefas. Esse metodo incrementa a variável compartilhada tarefas_disponiveis, por isso ele eh
	 synchronized. Salva na variavel strTarefas, tambem compartilhada, a tarefa na posição correspondente.
	 Chama a splitTarefa() descrita acima. E por fim, avisa todas as threads elevadores que possivelmente
	 podem estar esperando, que ja existe tarefa para ser executada.*/
	public synchronized void insereTarefa(String tarefa, int posicao){
		this.strTarefas[posicao] = tarefa;
		splitTarefa(strTarefas[posicao], posicao);
		tarefas_disponiveis++;
		notifyAll();
	}
	
	/*recebe o andar atual em que o elevador que chamou se encontra. Percorre a matriz 
	 de tarefas ate a posicao i que indica o numero de tarefas ja inseridas.
	 Se a tarefa ainda nao foi usada, pega o andar de partida da tarefa,
	 guarda a menor distancia entre o elevador e a tarefa e a posicao dessa tarefa na matriz 
	 decrementa tarefas inseridas e atraves de um vetor auxiliar, retorna a tarefa (uma linha da matriz)*/
	public synchronized int[] getTarefa(int andar_atual) throws InterruptedException{
		int partida = 0;
		int menor_distancia = n_andares + 1; //"infinito"
		int temp;
		int[] acabou_tarefa = new int[1];
		
		//enquanto nao houver tarefa disponivel, mas ainda houver tarefa para ser inserida pela main
		while(tarefas_disponiveis == 0 && acessaTarefas()){
			wait();
		}
		
		/*esse if verifica se acabaram as tarefas. Mas ainda tem elevador preso esperando tarefa, 
		entao eh preciso sair do metodo getTarefa e avisar a thread elevador que nao tem mais tarefas,
		para que ele saia do while.
		Evita o deadlock para o caso em que algum elevador nunca consiga realizar alguma tarefa e fique preso no wait. 
		EXEMPLO de deadlock: existe apenas mais uma tarefa para ser inserida. Mas os elevadores estao com CPU e consomem todas as
		tarefas disponiveis, tentam pegar mais e ficam presos no wait. Quando a main ganha CPU insere a ultima tarefa
		e libera os elevadores, somente um consegue pegar essa tarefa, e os outros continuam presos no wait. DEADLOCK!!
		*/
		if(!acessaTarefas()){
		acabou_tarefa[0] = -1;//avisar a thread elevador que acabaram as tarefas.
		return acabou_tarefa;
		}

		temp = tarefas_disponiveis;
		for(int i = 0; i < temp; i++){
			if(matriz_tarefas[i][0] != 0){ //se a tarefa ainda nao foi usada (excluida da possibilidade de uso)
				partida = matriz_tarefas[i][1];
				if(andar_atual > partida || andar_atual == partida){
					if((andar_atual - partida < menor_distancia)){ // calcula a menor distancia
						menor_distancia = andar_atual - partida;
						posicao = i; // guarda a posicao do vetor que tem a menor distancia
					}
				}
				else if(andar_atual < partida){ 
					if((partida - andar_atual < menor_distancia)){// calcula a menor distancia
						menor_distancia = partida - andar_atual;
						posicao = i;// guarda a posicao do vetor que tem a menor distancia
					}
				}
			}
			else 
				temp++;//para as outras vezes em que inserir tarefas
		}
		
		tarefas_disponiveis--;
				
		int[] aux = new int[4 + matriz_tarefas[posicao][3]];
		
		for(int i = 0; i < aux.length; i++)
			aux[i]= matriz_tarefas[posicao][i];
		
		matriz_tarefas[posicao][0] = 0; // serve para "excluir" a tarefa
		
		tarefas_acessadas++;// ja acessou uma tarefa
		return aux;
	}
	
	/*verifica se a variavel tarefas_acessadas eh menor que o total de tarefas(passado no arquivo de entrada),
	 se for quer dizer que ainda existe ou existira tarefas a serem executadas e retorna TRUE. Caso contrario,
	 todas as tarefas ja foram acessadas e retorna FALSE.*/
	public synchronized boolean acessaTarefas(){ // permite o acesso a lista de tarefas ate todas as tarefas serem realizadas
		if(tarefas_acessadas < n_tarefas)
			return true;
		else
			return false;
	}
	
}
