import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

public class Elevador extends Thread {
	// variaveis locais
	private int andar_partida_elevador;
	private int andar_atual;
	private int id_elevador;
	private int[] tarefa;
	private int andar_partida_tarefa;
	private int sentido_tarefa;
	private int n_requisicoes_tarefa;
	private int id_tarefa;
	Monitor m;
	EscreveNoArquivo escreveNoArquivo;

	/*o construtor recebe da classe Main o id do elevador, o andar de partida dele e o objeto da classe Monitor.*/
	public Elevador(int id_elevador, int andar_partida, Monitor m) {
		this.id_elevador = id_elevador;
		this.andar_partida_elevador = andar_partida;
		this.m = m;
		this.andar_atual = this.andar_partida_elevador;
		this.escreveNoArquivo = new EscreveNoArquivo("../Saidas/elevador" + id_elevador, true);
	}
	

	/*recebe como entrada um array de inteiros. Adiciona-os em um arrayList, que eh uma estrutura
	 de dados que nao aceita numeros repetidos, e depois passa do arrayList(com os numeros repetidos
	 ja excluidos) para um array comum novamente, e o retorna. */
	public int[] excluiIguais(int[] lista) {
		ArrayList<Integer> listaTemp = new ArrayList<Integer>();

		for (int i = 0; i < lista.length; i++) {
			if (i == 0) {
				listaTemp.add(lista[i]);
			} else if ((lista[i - 1] != lista[i])) {
				listaTemp.add(lista[i]);
			}
		}
		int[] listaNova = new int[listaTemp.size()];

		for (int i = 0; i < listaTemp.size(); i++) {
			listaNova[i] = listaTemp.get(i);
		}
		return listaNova;
	}

	/*recebe como entrada um array de inteiros(que eh a tarefa), o numero de requisicoes da tarefa,
	 e o sentido da tarefa. Esse metodo cria um array so das requisicoes(excluindo as tres primeiras
	 posicoes). Se o sentido for 1(sobe) ele ordena de forma crescente com o metodo Arrays.sort que
	 ja existe na classe Array. Mas se o sentido for 0(desce), usamos um objeto Integer da classe
	 Collections pois para ordenar de forma decrescente, Arrays.sort so ordena se for objeto de 
	 Collections, apos colocar na ordem decrescente passa de Integer para array de int[] novamente. 
	 Antes de retornar, o metodo excluiIguais() eh chamado para ja retornar o array 
	 na ordem certa, sem os numeros repetidos e sem as tres primeiras posicoes iniciais(apenas 
	 as requisicoes dos usuarios).*/
	public int[] ordenaTarefa(int[] tempInt, int requisicoes, int sentido_tarefa) {
		int[] listaNova = new int[requisicoes];
		for (int i = 4; i < tempInt.length; i++) {
			listaNova[i - 4] = tempInt[i];
		}
		if (sentido_tarefa == 1){
			Arrays.sort(listaNova);
		}
		else {
			Integer[] listaTemp = new Integer[listaNova.length];
			for (int i = 0; i < listaNova.length; i++)
				listaTemp[i] = new Integer(listaNova[i]);
			Arrays.sort(listaTemp, Collections.reverseOrder());
			for (int i = 0; i < listaTemp.length; i++) {
				listaNova[i] = listaTemp[i];
			}
		}
			listaNova = excluiIguais(listaNova);
		return listaNova;
	}
	

	/*recebe como entrada o andar de partida da tarefa, o numero de requisicoes, o sentido 
	 e o array de tarefas. Chama o metodo ordenaTarefa() e guarda em um array de inteiros o 
	 que ela retorna(requisicoes dos usuarios). Apos isso, escreve no arquivo as duas primeiras
	 linhas com a tarefa contendo todas as requisicoes (na ordem que chega do arquivo) e a tarefa 
	 ordenada e sem os repetidos. 
		A parte em que realmente desloca o elevador, usa dois arrays de inteiros auxiliares, um 
	 para salvar a tarefa ordenada e outro para colocar o que falta da tarefa apos deslocar 
	 ate a primeira requisicao, ou seja, com uma posicao a menos. A cada loop esses arrays sao
	 atualizados e eh escrito no arquivo de saida a linha com a situacao atual do elevador. Apos
	 o fim de cada tarefa eh testado se existe alguma tarefa ainda que nao foi acessada, caso nao
	 exista, eh escrito 'fim' no final do arquivo correspondente ao elevador.*/
	public void deslocaElevador(int andar_partida_tarefa, int requisicoes, int sentido, int[] tarefa) throws IOException {
		int[] tarefaOrdenada = ordenaTarefa(tarefa, requisicoes, sentido);
		
		//contem somente a lista dos andares da requisicao sem excluir os repetidos
		int[] listaAndares = new int[requisicoes];
		for (int i = 4; i < tarefa.length; i++) {
			listaAndares[i - 4] = tarefa[i];
		}

		//inicia a escrita
		escreveNoArquivo.escreve("nova tarefa\n");
		m.escreveArquivo(escreveNoArquivo, andar_atual, id_tarefa, tarefa[1], sentido, listaAndares);
		andar_atual = tarefa[1];
		m.escreveArquivo(escreveNoArquivo, andar_atual, id_tarefa, tarefa[1], sentido, tarefaOrdenada);
		
		//desloca realmente o elevador
		int tamAux = tarefaOrdenada.length;
		int[] novaListaAux = new int[tamAux];
		int[] novaListaAux2;
		
		novaListaAux = tarefaOrdenada;
		andar_atual = novaListaAux[0];
		for(int i = 0; i < tarefaOrdenada.length; i++){
			novaListaAux2 = new int [tamAux -1];
			for(int j = 1; j < tamAux; j++){
				novaListaAux2[j-1] = novaListaAux[j];
			}
			m.escreveArquivo(escreveNoArquivo, andar_atual, id_tarefa, this.andar_partida_tarefa, sentido, novaListaAux2);
			if(tamAux -1 != 0 )
				andar_atual = novaListaAux2[0];
			tamAux--;
			novaListaAux = novaListaAux2;
		}
		escreveNoArquivo.escreve("tarefa concluida\n");
		if(m.acessaTarefas() == false)
			escreveNoArquivo.escreve("fim");
	}

	int cont = 0;//pra saber qnts tarefas cada elevador realizou
	
	/*Esse metodo, que eh executado quando a thread eh disparada, fica em um loop enquanto
	 houver tarefas para serem acessadas. A cada iteracao ele chama o metodo do monitor getTarefa
	 que recebe o andar atual do elevador. Apos o retorno de getTarefa, o elevador verifica se 
	 realmente pegou uma tarefa ou se foi sinalizado pelo monitor que as tarefas acabaram antes
	 dele conseguir pegar uma tarefa disponivel. 
		Caso seja realmente uma tarefa, o elevador organiza as variaveis da lista de tarefas e
	 incrementa um contador (para ao final saber quantas tarefas cada elevador realizou) e chama
	 o método deslocaElevador() descrito acima. Caso contrario, ele sai do loop.*/
	public void run() {
		while(m.acessaTarefas()){
			try {
				tarefa = m.getTarefa(andar_atual);
			} catch (InterruptedException e) {e.printStackTrace();}
			
			
			if(tarefa[0] == -1){//verifica se ja acabaram as tarefas antes do elevador conseguir pegar alguma
				break;
			}
			
			id_tarefa = tarefa[0];
			andar_partida_tarefa = tarefa[1];
			sentido_tarefa = tarefa[2];
			n_requisicoes_tarefa = tarefa[3];
			cont++;
			try {
				deslocaElevador(andar_partida_tarefa, n_requisicoes_tarefa, sentido_tarefa, tarefa);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		System.out.println("ELEVADOR[" + this.id_elevador + "]" + " REALIZOU " + cont + " TAREFAS" );
	}
}
