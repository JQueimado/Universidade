public class Pawn implements Contrato.IPawn {

    public Route route;

    public Pawn(int x,int y){
        route=new Route(x,y);
    }

    public Pawn (Route route){
        this.route=new Route(route);
    }


    public Route getRoute() {
        return route;
    }

    public void move(Contrato.Move move) {
        route.move(move);
    }
}
