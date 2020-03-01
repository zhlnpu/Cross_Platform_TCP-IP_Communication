/*
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using LitJson;

// class ClientInfo
// Socket is the one that connect between client and server
// Address is the IP and port of Client
// NickName is defined by user, easy to recognize  sockets
// IsOpen is a flag that indicate socket is open or close
// EventList store many Events that can be implement by Client
public class ClientInfo
{
	public Socket socket { get; set; }
	public string address { get; set; }
	public string nickName { get; set; }
	public List<Func> funcList { get; set; }
	public ClientInfo()
	{
		funcList = new List<Func>();
	}
}


// Every client should have all of FunctionKeys, Only by this, can client send
// FunctionKey to other client  
public enum EventTypes
{
	Inform = 0,
	QuestionAnswer,
	Save,
	PPDL,
	OncePPDL ,
	Broadcast,
}

public class YSObject
{
	public String fromWhere { get; set; }
	public String toWhere { get; set; }
	public Object et { get; set; }
	public Object data { get; set; }
	public String dataType { get; set; }
	public YSObject() { }
	
	public YSObject(String fromWhere, String toWhere, Events et, Object data)
	{
		this.fromWhere = fromWhere;
		this.toWhere = toWhere;
		this.et = et;
		this.data = data;
		this.dataType = data.GetType().ToString();
	}
	public YSObject(String fromWhere, Events et, Object data)
	{
		this.fromWhere = fromWhere;
		this.toWhere = "Server";
		this.et = et;
		this.data = data;
		this.dataType = data.GetType().ToString();
	}
}

public class Events
{
	public string funcName { get; set; }
	public EventTypes eventType { get; set; }
	public Events() { }
	
	public Events(string funcName, EventTypes eventType)
	{
		this.funcName = funcName;
		this.eventType = eventType;
	}
}

public class Func
{
	public string funcName{ get; set; }
	public string dataType { get; set; }
	public Func() {}
	public Func( string funcName, string dataType )
	{
		this.funcName = funcName;
		this.dataType = dataType;
	}
}

public class FuncHandle
{
	public String fromWhere { get; set; }
	public Object func { get; set; }
	public FuncHandle() { }

	public FuncHandle(String fromWhere, Func func)
	{
		this.fromWhere = fromWhere;
		this.func = func;
	}
}

//三维坐标点
public class Point
{
	public double x { get; set; }
	public double y { get; set; }
	public double z { get; set; }
	public Point(){}
	public Point(double x, double y, double z)
	{
		this.x = x;
		this.y = y;
		this.z = z;
	}
	public Point(Point position)
	{
		this.x = position.x;
		this.y = position.y;
		this.z = position.z;
	}
}

public class DPMToProjector
{
	public List<Point> DPMcoordinate{ get; set;}
	public List<string> DPMinformation{ get; set;}
	
	public DPMToProjector()
	{
		DPMcoordinate = new List<Point>();
		DPMinformation = new List<string> ();
	}
}



*/
