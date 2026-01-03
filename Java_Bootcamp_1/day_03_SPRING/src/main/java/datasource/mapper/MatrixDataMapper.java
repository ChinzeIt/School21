package datasource.mapper;

import datasource.model.MatrixDataS;
import domain.model.Matrix;

public class MatrixDataMapper {
    public static MatrixDataS toDataSource(Matrix matrix) {
        int[][] newField=new int[3][3];

        for (int i=0; i<3; ++i)
            for (int j=0; j<3; ++j)
                newField[i][j]=matrix.get(i,j);

        return new MatrixDataS(newField);
    }

    public static Matrix toDomain(MatrixDataS matrix) {
        Matrix m = new Matrix();
        int[][] oldField = matrix.get();

        for (int i=0; i<3; ++i)
            for (int j=0; j<3; ++j)
                m.set(i, j, oldField[i][j]);

        return m;
    }
}
