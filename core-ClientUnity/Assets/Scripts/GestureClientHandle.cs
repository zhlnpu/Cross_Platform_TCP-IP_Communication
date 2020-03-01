/*
using UnityEngine;
using System.Collections;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.Net.Sockets;
using LitJson;

public class GestureClientHandle : ClientHandler {

	private Dictionary<string, bool> dict = new Dictionary<string, bool> ();


	private List<Point> buttonsOperation = new List<Point> ();
    private List<Point> buttonsSolution = new List<Point>();

	public GestureClientHandle( ): base(){ }

	public override void InitEventList( )
	{
		base.InitEventList( );
		clientInfo.nickName = "Gesture";
		clientInfo.funcList.Add(new Func("Save","String"));
        clientInfo.funcList.Add(new Func("InitialButtonsSolution", "List<Point>"));
        clientInfo.funcList.Add(new Func("InitialButtonsOperation", "List<Point>"));
		clientInfo.funcList.Add(new Func("Back","Bool"));

        dict.Add("InitialButtonsSolution", false);
        dict.Add("InitialButtonsOperation", false);
		dict.Add ("Reset", false);

	}

	public override void ClientDoProsess(string json)
	{
		JsonData jd  = JsonMapper.ToObject(json);
		string fromWhere = (string)jd["fromWhere"];
		JsonData jdet = jd["et"];
		Events et = deCodeEventByJd(jdet);
		JsonData jddt = jd["data"];
		switch(et.funcName)
		{
		case "Save":
			save(jd);
			break;
		case "InitialButtonsSolution":

			buttonsSolution.Clear();
			for( int i=0; i<jddt.Count; i++ )
			{
				buttonsSolution.Add( DecodePointByJd(jddt[i]) );
			}
            dict["InitialButtonsSolution"] = true;
            sendDatas(fromWhere, new Events("GestureReceivedSolutionButtons", EventTypes.PPDL), true);
			break;

        case "InitialButtonsOperation":

			buttonsOperation.Clear();
			for( int i=0; i<jddt.Count; i++ )
			{
				buttonsOperation.Add( DecodePointByJd(jddt[i]) );
			}
            dict["InitialButtonsOperation"] = true;
            sendDatas(fromWhere, new Events("GestureReceivedOperationButtons", EventTypes.PPDL), true);
			break;
		case "Back":
			dict["Reset"]=true;
		break;


		default:
			break;
		}
	}

	public void SetDic( Dictionary<string, bool> dic)
	{
		this.dict = dic;
	}

	public Dictionary<string, bool> GetDic()
	{
		return dict;
	}

	public List<Point> GetButtonsPositionOperation()
	{
		return buttonsOperation;
	}
    public List<Point> GetButtonsPositionSolution()
    {
        return buttonsSolution;
    }


	public Point DecodePointByJd( JsonData jd )
	{
		Point pt = new Point ();
		pt.x = (double)jd["x"];
		pt.y = (double)jd["y"];
		pt.z = (double)jd["z"];
		return pt;
	}
		public void Init()
		{
				buttonsOperation.Clear ();
				buttonsSolution.Clear ();

				dict ["InitialButtonsSolution"] = false;
				dict ["InitialButtonsOperation"] = false;
				dict ["Reset"] = false;

		}


}
*/
