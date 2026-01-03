package web.mapper;

import domain.model.Matrix;
import web.model.MatrixWeb;

public class MatrixWebMapper {
    public static MatrixWeb toWeb(Matrix matrix) {
        int[][] newField=new int[3][3];

        for (int i=0; i<3; ++i)
            for (int j=0; j<3; ++j)
                newField[i][j]=matrix.get(i,j);

        return new MatrixWeb(newField);
    }

    public static Matrix toDomain(MatrixWeb matrix) {
        Matrix m = new Matrix();
        int[][] oldField = matrix.getField();

        for (int i=0; i<3; ++i)
            for (int j=0; j<3; ++j)
                m.set(i, j, oldField[i][j]);

        return m;
    }
}
