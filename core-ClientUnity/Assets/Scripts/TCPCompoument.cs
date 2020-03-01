using UnityEngine;
using ServerCommunication;


public class TCPCompoument : MonoBehaviour
{
    //variables
    private TCPConnection myTCP;
    //private ModelingManager     myModelingManager;

 //   public EmotionFeddback emotionalData = new EmotionFeddback();

    void Start()
    {

        myTCP = gameObject.GetComponent<TCPConnection>();

       
      


        //kun
        //  C_KUN_POINT kun_point = new C_KUN_POINT((int)CLIENT_NAME.CN_UNITY_1, (int)DATA_TYPE.DT_POINT, 1.111, 2.222, 3.333);
        //   myTCP.SendToServer(kun_point.ToByteArray());





    }
    void Update()
    {
        // 		//keep checking the server for messages, if a message is received from server, it gets logged in the Debug console (see function below)
        // 		if (myTCP.socketReady == true) {
        // 
        // 
        // 
        // 			Base 
        // 			test.commandType = COMMAND_TYPE.CN_PROJECTOR;
        // 			test.dataType = DATA_TYPE.DT_TEST;
        // 
        // 			test.value = 123456;
        // 
        // 			SendToServer (test.ToByteArray ());
        // 
        // 		}
    }

    void OnGUI()
    {
        // if connection has not been made, display button to connect



        if (GUI.Button(new Rect(10, 10, 100, 100), "send test message"))
        {
            C_Test test = new C_Test(CLIENT_NAME.CN_UNITY_1, DATA_NAME.DN_TEST, DATA_TYPE.DT_POINT3);  


            test.value[0] = 1.1;
            test.value[1] = 2.1;
            test.value[2] = 3.1;


            /*    C_Test test = new C_Test(CLIENT_NAME.CN_UNITY_1, (int)DATA_TYPE.DT_ARDUINO, 1);*/
            myTCP.SendToServer(test.ToByteArray());

        }


    }

  

    /*
        public void SetData(C_CommandBase data)
        {
            switch(data.dataType)
            {
                case DATA_TYPE.DT_ARDUINO:
                    emotionalData.power = (C_Power)data;

                    break;
                    case DATA_TYPE.DT_POWER:
                    emotionalData.arduino = (C_Arduino)data;

                    break;
                    case DATA_TYPE.DT_CHAOS:


                    break;
            }
        


        }*/


}


