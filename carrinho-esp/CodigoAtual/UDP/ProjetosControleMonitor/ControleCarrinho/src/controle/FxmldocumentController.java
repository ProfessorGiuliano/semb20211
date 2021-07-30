/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controle;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.URL;
import java.net.UnknownHostException;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Slider;

/**
 * FXML Controller class
 *
 * @author Tales
 */
public class FxmldocumentController implements Initializable {
    byte[] sendData;
    @FXML
    private Button esquerda;
    @FXML
    private Button frente;
    @FXML
    private Button direita;
    @FXML
    private Button re;
    @FXML
    private Button leitura;
    @FXML
    private Slider velocidade;

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
    }    

    @FXML
    private void e(ActionEvent event) throws UnknownHostException, IOException {
        String comando = "esquerda/";
        comando += Math.round(velocidade.getValue());
        enviar(comando);
    }

    @FXML
    private void f(ActionEvent event) throws UnknownHostException, IOException{
        String comando = "frente/";
        comando += Math.round(velocidade.getValue());
        enviar(comando);
    }

    @FXML
    private void d(ActionEvent event) throws UnknownHostException, IOException{
        String comando = "direita/";
        comando += Math.round(velocidade.getValue());
        enviar(comando);
    }

    @FXML
    private void r(ActionEvent event) throws UnknownHostException, IOException{
        String comando = "re/";
        comando += Math.round(velocidade.getValue());
        enviar(comando);
    }

    @FXML
    private void ler(ActionEvent event) throws UnknownHostException, IOException {
        String comando = "leitura/";
        enviar(comando);
    }
    private void enviar(String entrada) throws SocketException, UnknownHostException, IOException {
        String msg = "carro/";
        msg += entrada;
        sendData = msg.getBytes();
        DatagramSocket clientSocket = new DatagramSocket();
        clientSocket.setBroadcast(true);
        InetAddress ipAddress = InetAddress.getByName("255.255.255.255");
        DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, ipAddress, 5050);
        clientSocket.send(sendPacket);
        clientSocket.close();
        System.out.println(msg);
    }
    
}
