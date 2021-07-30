/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controle;

import java.io.IOException;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 *
 * @author Tales
 */
public class aplicacao extends Application {
    private FXMLLoader fxmlLoader;
    private Parent parent;
    @Override
    public void start(Stage stage) {
         try {
            fxmlLoader = new FXMLLoader(getClass().getResource("fxmldocument.fxml"));
            parent = (Parent) fxmlLoader.load();
        } catch (IOException ex) {
            System.out.println("Erro " + ex.getMessage());
        }
         
        Scene scene = new Scene(parent);
        stage.setScene(scene);
        stage.setTitle("ControleCarrinho");
        stage.setResizable(false);
        stage.show();
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
    
}
