package domain.model;

public class Matrix {
    private int[][] field;
    public Matrix() {
        field = new int[3][3];
        for (int i=0; i<3; ++i)
            for (int j=0; j<3; ++j)
                field[i][j]=0;
    }
    public int get(int row, int col) {
        return field[row][col];
    }
    public void set (int row, int col, int value) {
        field[row][col]=value;
    }
}
