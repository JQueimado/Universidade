import java.util.ArrayList;

public class Route implements Contrato.IRoute {

    public ArrayList<Contrato.Move> route;
    public ArrayList<int[]> positions;

    public Route(int x,int y){
        route=new ArrayList<>();
        positions=new ArrayList<>();
        route.add(Contrato.Move.NOOP);
        int[] pos = new int[2];
        pos[0]=x;
        pos[1]=y;
        positions.add(pos);
    }
    public Route(Route route){
        ArrayList<Contrato.Move> newRoute= new ArrayList<>();
        ArrayList<int[]> newPositions=new ArrayList<>();
        newRoute.addAll(route.route);
        newPositions.addAll(route.positions);
        this.route=newRoute;
        this.positions=newPositions;
    }

    @Override
    public void move(Contrato.Move move) {
        route.add(move);
        int[] lastPosition=positions.get(positions.size()-1);
        int[] newPosition=new int[]{lastPosition[0],lastPosition[1]};
        switch (move){
            case NORT:newPosition[1]-=1;break;
            case SOUTH:newPosition[1]+=1;break;
            case WEST:newPosition[0]+=1;break;
            case EAST:newPosition[0]-=1;break;
        }
        positions.add(newPosition);

    }

    @Override
    public int getCol() {
        return positions.get(positions.size()-1)[0];
    }

    @Override
    public int getRow() {
        return positions.get(positions.size()-1)[1];
    }

    @Override
    public int length() {
        return route.size();
    }

    @Override
    public int getRow(int i) {
        return positions.get(i)[1];
    }

    @Override
    public int getCol(int i) {
        return positions.get(i)[0];
    }
}
