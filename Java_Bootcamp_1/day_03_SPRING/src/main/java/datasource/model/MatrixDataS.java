package datasource.model;

public class MatrixDataS {
    int[][] field;

    public MatrixDataS(int field[][]) {
        this.field=field;
    }

    public int[][] get() {
        return field;
    }
}
