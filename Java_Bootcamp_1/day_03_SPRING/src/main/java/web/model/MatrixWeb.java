package web.model;

import com.fasterxml.jackson.annotation.JsonProperty;

public class MatrixWeb {
    int[][] field;

    public MatrixWeb(int field[][]) {
        this.field=field;
    }

    public MatrixWeb() {
        this.field = new int[3][3];
    }

    public int[][] getField() {
        return field;
    }

    public void setField(int[][] field) {
        this.field = field;
    }
}
