public class Rechteck extends Form {
    private double breite, hoehe;

    public Rechteck(double x, double y, double breite, double hoehe)    {
        this.x = x;
        this.y = y;     // x und y von Form geerbt
        this.breite = breite;
        this.hoehe = hoehe;
    }

    public void setHoehe(double hoehe) {
        this.hoehe = hoehe;
    }

    public void setBreite(double breite) {
        this.breite = breite;
    }

    public double getHoehe()    {
        return hoehe;
    }

    public double getBreite() {
        return breite;
    }

    public double flaeche() {
        return breite*hoehe;
    }

    public String toString() {
        return "Rechteck(x = " + x + ",  y = " + y +
        "), \n\tBreite = " + breite + ", \n\tHoehe = " +
        hoehe + ",  \n" + String.format("\tFlaeche = %6.2f!\n",
        flaeche());
    }
}