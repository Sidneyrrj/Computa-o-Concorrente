import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.IOException;

public class EscreveNoArquivo {
	private String arquivoSaida;
	private boolean append_to_file;
	
	public EscreveNoArquivo(String arquivoSaida, boolean append_to_file){
		this.arquivoSaida = arquivoSaida;
		this.append_to_file = append_to_file;
	}
	public void escreve( String texto ) throws IOException {
		FileWriter fw = new FileWriter(arquivoSaida , append_to_file);
		PrintWriter pw = new PrintWriter(fw);
		
		pw.printf( "%s" , texto);	
		pw.close();
	}	
}