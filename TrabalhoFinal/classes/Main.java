import java.io.FileNotFoundException;
import java.io.IOException;

public class Main {

	public static void main(String[] args){
		double tempoInicio = System.currentTimeMillis();
		String entrada = "../Entradas/teste";
		
		// N andares, M elevadores e R requisicoes(numero maximo de usuarios por elevador)
		int N, M, R, n_tarefas;
		
		try {
			LeitorDeArquivo leitor = new LeitorDeArquivo(entrada);
			String[] linhas = leitor.abreArquivo();
			String[] aux0 = linhas[0].split(" ");
			String[] aux1 = linhas[1].split(" ");
			String[] aux2 = linhas[2].split(" ");
		
			//pega os numeros da primeira linha do arquivo e seta os valores de N, M e R, passando de String pra int			
			N = Integer.parseInt(aux0[0]);
			M = Integer.parseInt(aux0[1]);
			R = Integer.parseInt(aux0[2]);
			n_tarefas = Integer.parseInt(aux2[0]);

			Monitor monitor = new Monitor(R, N, n_tarefas);
			Elevador[] elevador = new Elevador[M];

			
			//cria o array das threads elevadores
			for (int i = 0; i < M; i++) {
				elevador[i] = new Elevador(i+1, Integer.parseInt((aux1[i])), monitor);
				elevador[i].start();
			}
			
			//adiciona o id na tarefa, e tenta inseri-la na matriz de tarefas
			String tarefa, id;
			for (int i = 1; i <= n_tarefas; i++) {
				tarefa = linhas[i + 2];
				id = i + " ";
				tarefa = id.concat(tarefa);
				monitor.insereTarefa(tarefa, i-1);
			}
			
			//espera as threads terminarem
			for (int i = 0; i < elevador.length; i++) {
				try {
					elevador[i].join();
				} catch (InterruptedException e) {
					return;
				}
			}
			double tempoFim = System.currentTimeMillis();
			double tempoTotal = (tempoFim - tempoInicio)/1000;
			
			System.out.println("Tempo total gasto: " + tempoTotal + "s");
			System.out.println("Thread principal(main) acabou!!!");
			
		} catch (IOException e) {
			System.out.println(e.getMessage());
		}
	}
}
