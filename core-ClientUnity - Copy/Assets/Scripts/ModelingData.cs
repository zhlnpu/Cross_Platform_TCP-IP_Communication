//using System;
//using System.Collections;
//
//namespace ServerCommunication
//{
//    public enum DataType
//    {
//        DT_BASE             = 100,
//        DT_POINT            = 101,
//        DT_POLYLINE         = 102,
//        DT_PATH             = 103,
//        DT_MODELRAW         = 104,
//        DT_MODELMESH        = 105,
//    };
//
//    public enum ActuratorCommand
//    {
//        AC_EMPTY = 0,
//        AC_UNDO = 1,
//        AC_CUR = 2,     // Tip position
//        AC_DOWN = 3,        // Tip down position
//        AC_UP = 4,      // Tip up position
//    };
//
//    public class Modeling
//    {
//        public DataType type;
//        public Int32 count;
//        public Int32 id;
//        public ActuratorCommand command;
//
//        public virtual byte[] ToByteArray()
//        {
//            count = byte_size();
//
//            byte[] _type = BitConverter.GetBytes((Int32)type);
//            byte[] _count = BitConverter.GetBytes(count);
//
//            byte[] _id = BitConverter.GetBytes(id);
//            byte[] _command = BitConverter.GetBytes((Int32)command);
//
//            byte[] ret = new byte[byte_size()];
//
//            _type.CopyTo(ret, 0);
//            _count.CopyTo(ret, _type.Length);
//            _id.CopyTo(ret, _type.Length + _count.Length);
//            _command.CopyTo(ret, _count.Length + _id.Length + _type.Length);
//
//            return ret;
//        }
//
//        public virtual Int32 byte_size()
//        {
//            return sizeof(DataType) + sizeof(Int32) + sizeof(Int32) + sizeof(ActuratorCommand);
//        }
//
//        public Modeling()
//        {
//            id = -1;
//            type = DataType.DT_BASE;
//            command = ActuratorCommand.AC_EMPTY;
//        }
//
//        public Modeling(byte[] data, int index = 0)
//        {
//            type = (DataType)BitConverter.ToInt32(data, index);
//            count = BitConverter.ToInt32(data, index + sizeof(DataType));
//            id = BitConverter.ToInt32(data, index + sizeof(Int32) + sizeof(DataType));
//            command = (ActuratorCommand)BitConverter.ToInt32(data, index + sizeof(Int32) + sizeof(Int32) + sizeof(DataType));
//        }
//    };
//
//    public class Point : Modeling
//    {
//        public float x;
//        public float y;
//        public float z;
//
//        public override byte[] ToByteArray()
//        {
//            byte[] _base = base.ToByteArray();
//
//            byte[] _x = BitConverter.GetBytes(x);
//            byte[] _y = BitConverter.GetBytes(y);
//            byte[] _z = BitConverter.GetBytes(z);
//
//            byte[] ret = new byte[byte_size()];
//
//            _base.CopyTo(ret, 0);
//            _x.CopyTo(ret, _base.Length);
//            _y.CopyTo(ret, _base.Length + _x.Length);
//            _z.CopyTo(ret, _base.Length + _x.Length + _y.Length);
//
//            return ret;
//        }
//
//        public override Int32 byte_size()
//        {
//            return base.byte_size() + sizeof(float) * 3;
//        }
//
//        public Point()
//        {
//            type = DataType.DT_POINT; command = ActuratorCommand.AC_EMPTY;
//        }
//
//        public Point(float _x, float _y, float _z)
//        {
//            type = DataType.DT_POINT;
//            command = ActuratorCommand.AC_EMPTY;
//            x = _x; y = _y; z = _z;
//        }
//
//        public Point(byte[] data, int index = 0) : base(data, index)
//        {
//            x = BitConverter.ToSingle(data, index + base.byte_size());
//            y = BitConverter.ToSingle(data, index + base.byte_size() + sizeof(float));
//            z = BitConverter.ToSingle(data, index + base.byte_size() + sizeof(float) * 2);
//        }
//    };
//
//    public class Polyline : Modeling
//    {
//        public ArrayList points = new ArrayList();
//
//        public override byte[] ToByteArray()
//        {
//            byte[] _base = base.ToByteArray();
//
//            byte[] ret = new byte[byte_size()];
//
//            _base.CopyTo(ret, 0);
//            int index = _base.Length;
//
//            int count = points.Count;
//            byte[] len = BitConverter.GetBytes((Int32)count);
//            len.CopyTo(ret, index);
//            index += len.Length;
//
//            for(int i = 0; i < points.Count; i++)
//            {
//                byte[] pt = (points[i] as Point).ToByteArray();
//                pt.CopyTo(ret, index);
//
//                index += pt.Length;
//            }
//
//            return ret;
//        }
//
//        public override Int32 byte_size()
//        {
//            int index = base.byte_size() + sizeof(Int32);
//            for (int i = 0; i < points.Count; i++)
//                index += (points[i] as Point).byte_size();
//
//            return index;
//        }
//
//        public Polyline()
//        {
//            type = DataType.DT_POLYLINE; command = ActuratorCommand.AC_EMPTY;
//        }
//
//        public Polyline(byte[] data, int start = 0) : base(data, start)
//        {
//            int index = start + base.byte_size();
//
//            int count = BitConverter.ToInt32(data, index);
//            index += sizeof(Int32);
//
//            for (int i = 0; i < count; i++)
//            {
//                Point pt = new Point(data, index);
//
//                points.Add(pt);
//
//                index += pt.byte_size();
//            }
//        }
//    };
//
//    public class Path : Modeling
//    {
//        public ArrayList points = new ArrayList();
//
//        public override byte[] ToByteArray()
//        {
//            byte[] _base = base.ToByteArray();
//
//            byte[] ret = new byte[byte_size()];
//
//            _base.CopyTo(ret, 0);
//            int index = _base.Length;
//
//            int count = points.Count;
//            byte[] len = BitConverter.GetBytes((Int32)count);
//            len.CopyTo(ret, index);
//            index += len.Length;
//
//            for (int i = 0; i < points.Count; i++)
//            {
//                byte[] pt = (points[i] as Point).ToByteArray();
//                pt.CopyTo(ret, index);
//
//                index += pt.Length;
//            }
//
//            return ret;
//        }
//
//        public override Int32 byte_size()
//        {
//            int index = base.byte_size() + sizeof(Int32);
//            for (int i = 0; i < points.Count; i++)
//                index += (points[i] as Point).byte_size();
//
//            return index;
//        }
//
//        public Path()
//        {
//            type = DataType.DT_PATH; command = ActuratorCommand.AC_EMPTY;
//        }
//
//        public Path(byte[] data, int start = 0) : base(data, start)
//        {
//            int index = start + base.byte_size();
//
//            int count = BitConverter.ToInt32(data, index);
//            index += sizeof(Int32);
//
//            for (int i = 0; i < count; i++)
//            {
//                Point pt = new Point(data, index);
//
//                points.Add(pt);
//
//                index += pt.byte_size();
//            }
//        }
//    };
//
//    public class ModelRaw : Modeling
//    {
//        // Modeling data
//        public Polyline polyline = new Polyline();
//        public Path         path = new Path();
//
//        public override byte[] ToByteArray()
//        {
//            byte[] _base = base.ToByteArray();
//
//            byte[] ret = new byte[byte_size()];
//
//            _base.CopyTo(ret, 0);
//            int index = _base.Length;
//
//            // polyline --------------------------------
//            byte[] _polyline = polyline.ToByteArray();
//
//            int len = _polyline.Length;
//            byte[] l_p = BitConverter.GetBytes((Int32)len);
//            l_p.CopyTo(ret, index);
//            index += l_p.Length;
//
//            _polyline.CopyTo(ret, index);
//            index += _polyline.Length;
//
//            // path ------------------------------------
//            byte[] _path = path.ToByteArray();
//
//            len = _path.Length;
//            l_p = BitConverter.GetBytes((Int32)len);
//            l_p.CopyTo(ret, index);
//            index += l_p.Length;
//
//            _path.CopyTo(ret, index);
//
//            return ret;
//        }
//
//        public override Int32 byte_size()
//        {
//            int index = base.byte_size();
//
//            index += sizeof(Int32);
//            index += polyline.byte_size();
//            index += sizeof(Int32);
//            index += path.byte_size();
//
//            return index;
//        }
//
//        public bool isRevolution()
//        {
//            if (path.points.Count == 0)
//                return false;
//
//            float n = 0;
//            for (int i = 0; i < path.points.Count; i++)
//            {
//                Point pt = path.points[i] as Point;
//                n += pt.z;
//            }
//
//            if (n == 0)
//                return true;
//            else
//                return false;
//        }
//
//        public ModelRaw()
//        {
//            type = DataType.DT_MODELRAW; command = ActuratorCommand.AC_EMPTY;
//        }
//
//        public ModelRaw(byte[] data, int start = 0) : base(data, start)
//        {
//            int index = base.byte_size();
//
//            // polyline -----------------------------------------------------
//            polyline = new Polyline(data, index);
//            index += polyline.byte_size();
//
//            // path ---------------------------------------------------------
//            path = new Path(data, index);
//            index += path.byte_size();
//        }
//    };
//
//    public class ModelMesh : Modeling
//    {
//        // Display data
//        public ArrayList points     = new ArrayList();             // x, y, z, x, y, z ...
//        public ArrayList normals    = new ArrayList();            // nx, ny, nz, nx, ny, nz ...
//        public ArrayList triangles  = new ArrayList();          // ix, iy, iz, ix, iy, iz ...
//        public ArrayList domains    = new ArrayList();            // ic, ic, ic, ic ...
//
//        public override byte[] ToByteArray()
//        {
//            byte[] _base = base.ToByteArray();
//
//            byte[] ret = new byte[byte_size()];
//
//            _base.CopyTo(ret, 0);
//            int index = _base.Length;
//
//            // points -------------------------------
//            int len = points.Count;
//            byte[] l_p = BitConverter.GetBytes((Int32)len);
//            l_p.CopyTo(ret, index);
//            index += sizeof(Int32);
//
//            for (int i = 0; i < points.Count; i++)
//            {
//                byte[] val = BitConverter.GetBytes((float)points[i]);
//                val.CopyTo(ret, index);
//
//                index += val.Length;
//            }
//
//            // normals ------------------------------
//            len = normals.Count;
//            l_p = BitConverter.GetBytes((Int32)len);
//            l_p.CopyTo(ret, index);
//            index += sizeof(Int32);
//
//            for (int i = 0; i < normals.Count; i++)
//            {
//                byte[] val = BitConverter.GetBytes((float)normals[i]);
//                val.CopyTo(ret, index);
//
//                index += val.Length;
//            }
//
//            // triangles --------------------------------
//            len = triangles.Count;
//            l_p = BitConverter.GetBytes((Int32)len);
//            l_p.CopyTo(ret, index);
//            index += sizeof(Int32);
//
//            for (int i = 0; i < triangles.Count; i++)
//            {
//                byte[] val = BitConverter.GetBytes((Int32)triangles[i]);
//                val.CopyTo(ret, index);
//
//                index += val.Length;
//            }
//
//            // domains --------------------------------
//            len = domains.Count;
//            l_p = BitConverter.GetBytes((Int32)len);
//            l_p.CopyTo(ret, index);
//            index += sizeof(Int32);
//
//            for (int i = 0; i < domains.Count; i++)
//            {
//                byte[] val = BitConverter.GetBytes((Int32)domains[i]);
//                val.CopyTo(ret, index);
//
//                index += val.Length;
//            }
//
//            return ret;
//        }
//
//        public override Int32 byte_size()
//        {
//            int index = base.byte_size();
//
//            index += sizeof(Int32);
//            index += points.Count * sizeof(float);
//            index += sizeof(Int32);
//            index += normals.Count * sizeof(float);
//            index += sizeof(Int32);
//            index += triangles.Count * sizeof(Int32);
//            index += sizeof(Int32);
//            index += domains.Count * sizeof(Int32);
//
//            return index;
//        }
//
//        public void AddTriangle(float[] point, float[] normal)
//        {
//            int index = points.Count / 3;
//
//            for (int i = 0; i < 9; i++)
//                points.Add(points[i]);
//
//            for (int i = 0; i < 3; i++)
//                normals.Add(normal[i]);
//
//            triangles.Add(index + 1);
//        }
//
//        public ModelMesh()
//        {
//            type = DataType.DT_MODELMESH; command = ActuratorCommand.AC_EMPTY;
//        }
//
//        public ModelMesh(byte[] data, int start = 0) : base(data, start)
//        {
//            int index = base.byte_size();
//
//            // points -----------------------------------------------------
//            int len = BitConverter.ToInt32(data, index);
//            index += sizeof(Int32);
//
//            for (int i = 0; i < len; i++)
//            {
//                float val = BitConverter.ToSingle(data, index);
//                points.Add(val);
//                index += sizeof(float);
//            }
//
//            // normals -----------------------------------------------------
//            len = BitConverter.ToInt32(data, index);
//            index += sizeof(Int32);
//
//            for (int i = 0; i < len; i++)
//            {
//                float val = BitConverter.ToSingle(data, index);
//                normals.Add(val);
//                index += sizeof(float);
//            }
//
//            // triangles -----------------------------------------------------
//            len = BitConverter.ToInt32(data, index);
//            index += sizeof(Int32);
//
//            for (int i = 0; i < len; i++)
//            {
//                Int32 val = BitConverter.ToInt32(data, index);
//                triangles.Add(val);
//                index += sizeof(float);
//            }
//
//            // domains ------------------------------------------------------
//            len = BitConverter.ToInt32(data, index);
//            index += sizeof(Int32);
//
//            for (int i = 0; i < len; i++)
//            {
//                Int32 val = BitConverter.ToInt32(data, index);
//                domains.Add(val);
//                index += sizeof(float);
//            }
//        }
//    };
//}