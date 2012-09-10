import java.util.ArrayList;
import java.util.List;


public class FormContainer {
	
	private List<Form> lstForm; //Array welches "form"-Objekte beinhaltet
	
	public FormContainer(){
		lstForm = new ArrayList<Form>();
	}
	
	public void add(Form f) {
				lstForm.add(f);
				System.out.println("Form zu Array hinzugefügt!");
	}

	public double gesamtFlaeche() {
		double summe = 0;
		
		for(Form f : lstForm) {  // loopt durch array
			summe += f.flaeche();  // zählt alle flächen der jeweiligen objekte zusammen
		}
		
		return summe;
	}

}

