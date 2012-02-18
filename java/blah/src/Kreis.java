
public class Kreis extends Form {
    private double radius;

    public Kreis(double x, double y, double radius) {
        this.x = x;
        this.x = y;         // x und y von Form geerbt
        this.radius = radius;
    }


    public void setRadius(double radius) {
        this.radius = radius;
    }


    public double getRadius() {
        return radius;
    }

    public double flaeche() {
        return Math.PI*radius*radius;
    }

    public String toString() {
        return "Kreis(x = " + x + ",  y = " + y +
            "), \n\tRadius r = " + radius + ", \n" +
            String.format("\tFlaeche = %6.2f!\n", flaeche());
    }
}
