using System;
using System.Collections.Generic;

namespace ServerCommunication
{
    public enum CLIENT_NAME
    {
        COMMAND_CONNECTION = 0,
        CN_PC_1 = 101,
        CN_PC_2 = 102,
        CN_PC_3 = 103,
        CN_PC_4 = 104,
        CN_PC_5 = 105,

        CN_UNITY_1 = 201,
        CN_UNITY_2 = 202,
        CN_UNITY_3 = 203,
        CN_UNITY_4 = 204,
        CN_UNITY_5 = 205,

        CN_ANDROID_1 = 301,
        CN_ANDROID_2 = 302,
        CN_ANDROID_3 = 303,
        CN_ANDROID_4 = 304,
        CN_ANDROID_5 = 305,

        CN_HOLOLENS_1 = 401,
        CN_HOLOLENS_2 = 402,
        CN_HOLOLENS_3 = 403,
        CN_HOLOLENS_4 = 404,
        CN_HOLOLENS_5 = 405,
    };

    public enum DATA_NAME
    {
        DN_TEST = 0,
        DT_ARDUINO = 1,
        DT_POWER = 2,
        DT_CHAOS = 3,
    };


    //kun
    public enum DATA_TYPE
    {
        DT_POINT = 0,
        DT_POINT3 = 1,
    };


// 
// 
//     public class EmotionFeddback
//     {
//         public Dictionary<string, bool> dic = new Dictionary<string, bool>();
// 
//         public C_Power power;
//         public C_Arduino arduino;
// 
//         public EmotionFeddback()
//         {
//             dic.Add("Received power", false);
//             dic.Add("Received arduino", false);
//         }
//     }

    public class C_CommandBase
    {
        public CLIENT_NAME whom;
        //      public CLIENT_NAME clientType;
        //   public DATA_TYPE dataType;

        public virtual byte[] ToByteArray()
        {
            byte[] _commandType = BitConverter.GetBytes((Int32)whom);
            // byte[] _dataType = BitConverter.GetBytes((Int32)dataType);
            //byte[] _val = BitConverter.GetBytes((Int32)value);

            byte[] ret = new byte[_commandType.Length /*+ _dataType.Length*/];

            _commandType.CopyTo(ret, 0);
            //   _dataType.CopyTo(ret, _commandType.Length);
            //      r  _val.CopyTo(ret, _base.Length + _cmd.Length);

            return ret;
        }
        public C_CommandBase(CLIENT_NAME _commandType)
        {
            whom = _commandType;
            // dataType = (DATA_TYPE)_dataType;
        }


        public C_CommandBase(byte[] data)
        {
            whom = (CLIENT_NAME)BitConverter.ToInt32(data, 0);
            //   dataType = (DATA_TYPE)BitConverter.ToInt32(_data, sizeof(Int32));

            //dataType = (DataName)BitConverter.ToInt32(data, byte_size());
        }

    }

    public class BaseDatatype : C_CommandBase
    {
        public DATA_NAME dataName;
        public DATA_TYPE dataType;

        public int length= sizeof(CLIENT_NAME)+   sizeof(DATA_NAME)+ sizeof(DATA_TYPE);


        public BaseDatatype(CLIENT_NAME __whom, DATA_NAME __dataName, DATA_TYPE __dataType) : base(__whom)
        {
            dataName = __dataName;
            dataType = __dataType;
        }

        public BaseDatatype(byte[] data) : base(data)
        {
            int pos = sizeof(CLIENT_NAME);
            int len = sizeof(DATA_NAME);
            dataName = (DATA_NAME)BitConverter.ToInt32(data, pos);
            pos += len;

            len = sizeof(DATA_TYPE);
            dataType = (DATA_TYPE)BitConverter.ToInt32(data, pos);
            pos += len;

        }

        public override byte[] ToByteArray()
        {
            byte[] byte_whom = base.ToByteArray();
            byte[] byte_dataName = BitConverter.GetBytes((int)dataName);
            byte[] byte_dataType = BitConverter.GetBytes((int)dataType);

            byte[] ret = new byte[byte_whom.Length + byte_dataName.Length + byte_dataType.Length];

            byte_whom.CopyTo(ret, 0);
            byte_dataName.CopyTo(ret, byte_whom.Length);
            byte_dataType.CopyTo(ret, byte_whom.Length + byte_dataName.Length);

            return ret;
        }
    }


    public class C_Test : BaseDatatype
    {
        //add extra codes here
        public double[] value = new double[3];
        public override byte[] ToByteArray()
        {
            byte[] byte_base = base.ToByteArray();
            byte[] byte_value = Converter.ConvertToByte(value);

            byte[] ret = new byte[byte_base.Length + byte_value.Length];

            byte_base.CopyTo(ret, 0);
            byte_value.CopyTo(ret, byte_base.Length);


            return ret;
        }
        //         public C_Test(int _commandType, int _dataTypem, int _value)
        //             : base(_commandType)
        //         {
        //             value = _value;
        //         }


        public C_Test(byte[] data) : base(data)
        {
            value = Converter.ConvertToDoubleArray(data, base.length, value.Length);
        }

        public C_Test(CLIENT_NAME __whom, DATA_NAME __dataName, DATA_TYPE __dataType) : base(__whom,  __dataName,  __dataType)
        {

        }

    }
    


    public class Converter
    {
        public static byte[] ConvertToByte(float[] data)
        {

            byte[] ret = new byte[data.Length * sizeof(float)];
            for (int i = 0; i < data.Length; i++)
            {
                (BitConverter.GetBytes((float)data[i])).CopyTo(ret, i * sizeof(float));
            }
            return ret;
        }
        public static float[] ConvertToFloatArray(byte[] data, int index, int length)
        {
            float[] result = new float[length];
            for (int i = 0; i < length; i++)
            {
                result[i] = BitConverter.ToSingle(data, index + i * sizeof(float));
            }
            return result;
        }
        public static byte[] ConvertToByte(double[] data)
        {

            byte[] ret = new byte[data.Length * sizeof(double)];
            for (int i = 0; i < data.Length; i++)
            {
                (BitConverter.GetBytes((double)data[i])).CopyTo(ret, i * sizeof(double));
            }
            return ret;
        }
        public static double[] ConvertToDoubleArray(byte[] data, int index, int length)
        {
            double[] result = new double[length];
            for (int i = 0; i < length; i++)
            {
                result[i] = BitConverter.ToDouble(data, index + i * sizeof(double));
            }
            return result;
        }
        public static byte[] ConvertToByte(int[] data)
        {
            byte[] ret = new byte[data.Length * sizeof(Int32)];
            for (int i = 0; i < data.Length; i++)
            {
                (BitConverter.GetBytes((int)data[i])).CopyTo(ret, i * sizeof(Int32));
            }
            return ret;
        }
        public static int[] ConvertToIntArray(byte[] data, int index, int length)
        {
            int[] result = new int[length];
            for (int i = 0; i < length; i++)
            {
                result[i] = BitConverter.ToInt32(data, index + i * sizeof(Int32));
            }
            return result;
        }
    }
}


