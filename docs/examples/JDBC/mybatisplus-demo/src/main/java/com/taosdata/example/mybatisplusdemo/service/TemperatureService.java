package com.taosdata.example.mybatisplusdemo.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import org.springframework.stereotype.Service;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

@Service
public class TemperatureService {
    @Autowired
    private DatabaseConnectionService databaseConnectionService;

    public void createTable(String tableName, String location, int tbIndex) throws SQLException {


        try (Connection connection = databaseConnectionService.getConnection();
             Statement statement = connection.createStatement()) {
            // 执行 SQL 查询
            statement.executeUpdate("create table " + tableName +  " using temperature tags( '" + location +"', " + tbIndex + ")");
        }
    }
}
