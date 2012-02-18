public class Formdemo {
    public static void main( String args[] ) {
        Rechteck re = new Rechteck(1.0, 1.0, 4.0, 5.0);
        Kreis kr = new Kreis(0.0, 0.0, 5.0);
        FormContainer cont = new FormContainer();
        
        System.out.println(kr);
        System.out.println(re);
        
        cont.add(kr);
        cont.add(re);

        System.out.print("Die Summe aller Flaechen betraegt: ");
        System.out.printf(" %6.2f\n\n", cont.gesamtFlaeche());
    }
}

