import com.google.gson.Gson;
import com.j256.ormlite.dao.Dao;
import com.j256.ormlite.dao.DaoManager;
import com.j256.ormlite.jdbc.JdbcConnectionSource;
import com.j256.ormlite.support.ConnectionSource;
import com.j256.ormlite.table.TableUtils;
import model.Distance;
import spark.ModelAndView;
import spark.Spark;
import spark.template.velocity.VelocityTemplateEngine;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Main {

    private static Dao getUrlORMLiteDao() throws SQLException {
        final String URI = "jdbc:sqlite:./JBApp.db";
        ConnectionSource connectionSource = new JdbcConnectionSource(URI);
//        TableUtils.dropTable(connectionSource, Distance.class,true);
        TableUtils.createTableIfNotExists(connectionSource, Distance.class);
        return DaoManager.createDao(connectionSource, Distance.class);
    }

    public static void main(String[] args) {

        final int PORT_NUM = 7000;
        Spark.port(PORT_NUM);
        Spark.staticFiles.location("/public");


        // show (read) all distance
        Spark.get("/", (req, res) -> {
            List<Distance> ls_d= getUrlORMLiteDao().queryForAll();
            Distance ls= new Distance("0");
            if (ls_d.size()!=0){
            ls = (Distance) getUrlORMLiteDao().queryBuilder().orderBy("id", false).limit(1L).query().get(0);}
            else{ls= new Distance("0");
            }
            Map<String, Object> model = new HashMap<String, Object>();
            model.put("distances", ls);
            return new ModelAndView(model, "public/index.vm");
        }, new VelocityTemplateEngine());

       //add url
        Spark.post("/", (req, res) -> {
            String distance = req.queryParams("distance");
            Distance em = new Distance(distance);
            getUrlORMLiteDao().create(em);
            res.status(201);
            res.type("application/json");
            return new Gson().toJson(em.toString());
        });


    }
}
