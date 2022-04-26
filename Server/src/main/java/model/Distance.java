package model;

import com.j256.ormlite.field.DatabaseField;
import com.j256.ormlite.table.DatabaseTable;

import java.net.MalformedURLException;
import java.net.URL;
import java.util.Arrays;
import java.util.Objects;


@DatabaseTable(tableName = "distances")
public class Distance {

    @DatabaseField(generatedId = true, columnName = "id")
    public Integer id;
    @DatabaseField(columnName = "distance")
    private String distance;


    public Distance() {
    }

    public Distance(String distance) {
        this.distance = distance;
    }

    public String getDistance() {
        return distance;
    }

    @Override
    public String toString() {

        return "Distance{" +
                "distance=" + distance +
                '}';
    }

    public Object getId() {
        return id;
    }
}
