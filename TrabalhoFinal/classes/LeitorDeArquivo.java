import java.io.IOException;
import java.io.FileReader;
import java.io.BufferedReader;

public class LeitorDeArquivo {
	private String entrada;

	public LeitorDeArquivo(String entrada) {
		this.entrada = entrada;
	}

	public int numeroDeLinhas() throws IOException {
		FileReader fr = new FileReader(entrada);
		BufferedReader br = new BufferedReader(fr);

		String linha;
		int total = 0;
		while ((linha = br.readLine()) != null) {
			total++;
		}
		br.close();
		return total;
	}

	public String[] abreArquivo() throws IOException {
		FileReader fr = new FileReader(entrada);
		BufferedReader br = new BufferedReader(fr);

		int linhas = numeroDeLinhas();
		String[] texto = new String[linhas];

		for (int i = 0; i < linhas; i++) {
			texto[i] = br.readLine();
		}
		br.close();
		return texto;
	}
}