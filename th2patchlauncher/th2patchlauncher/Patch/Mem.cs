﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;

namespace thps2patch
{
    class Mem
    {
        const int PROCESS_VM_READ = 0x0010;
        const int PROCESS_VM_MAGIC = 0x1F0FFF;

        const int PROCESS_VM_WRITE = 0x0020;
        const int PROCESS_VM_OPERATION = 0x0008;



        [DllImport("kernel32.dll")]
        public static extern IntPtr OpenProcess(int dwDesiredAccess, bool bInheritHandle, int dwProccessId);

        [DllImport("kernel32.dll")]
        public static extern bool ReadProcessMemory(int hProcess, int lpBaseAddress, byte[] lpBuffer, int dwSize, ref int lpNumberOfBytesRead);

        [DllImport("Kernel32.dll")]
        static extern bool WriteProcessMemory(int hProcess, int lpBaseAddress, byte[] lpBuffer, int dwSize, ref int lpNumberOfBytesWritten);

        private Process process;
        private IntPtr processHandle;

        bool ready = false;

        public Mem()
        {
        }

        public Mem(string pn)
        {
            try
            {
                process = Process.GetProcessesByName(pn)[0];
                ready = true;
            }
            catch
            {
                ready = false;
            }
        }


        public float ReadFloat(int where)
        {
            IntPtr processHandle = OpenProcess(PROCESS_VM_READ, false, process.Id);

            int bytesRead = 4;
            byte[] buffer = new byte[4];

            ReadProcessMemory((int)processHandle, where, buffer, buffer.Length, ref bytesRead);

            return BitConverter.ToSingle(buffer, 0);
        }

        public int ReadInt(int where)
        {
            IntPtr processHandle = OpenProcess(PROCESS_VM_READ, false, process.Id);

            int bytesRead = 4;
            byte[] buffer = new byte[4];

            ReadProcessMemory((int)processHandle, where, buffer, buffer.Length, ref bytesRead);

            return BitConverter.ToInt32(buffer, 0);
        }

        public uint ReadUInt32(int where)
        {
            IntPtr processHandle = OpenProcess(PROCESS_VM_READ, false, process.Id);

            int bytesRead = 4;
            byte[] buffer = new byte[4];

            ReadProcessMemory((int)processHandle, where, buffer, buffer.Length, ref bytesRead);

            return BitConverter.ToUInt32(buffer, 0);
        }

        public byte ReadByte(int where)
        {
            IntPtr processHandle = OpenProcess(PROCESS_VM_READ, false, process.Id);

            int bytesRead = 1;
            byte[] buffer = new byte[1];

            ReadProcessMemory((int)processHandle, where, buffer, buffer.Length, ref bytesRead);

            return buffer[0];
        }

        public void WriteArray(int where, byte[] wr)
        {
            IntPtr processHandle = OpenProcess(PROCESS_VM_MAGIC, false, process.Id);

            int bytesWritten = wr.Length;
            byte[] buffer = wr;

            WriteProcessMemory((int)processHandle, where, buffer, buffer.Length, ref bytesWritten);
        }

        public void WriteFloat(int where, float wr)
        {
            IntPtr processHandle = OpenProcess(PROCESS_VM_MAGIC, false, process.Id);

            int bytesWritten = 4;
            byte[] buffer = BitConverter.GetBytes(wr);

            WriteProcessMemory((int)processHandle, where, buffer, buffer.Length, ref bytesWritten);
        }

        public void WriteByte(int where, byte wr)
        {
            IntPtr processHandle = OpenProcess(PROCESS_VM_MAGIC, false, process.Id);

            int bytesWritten = 1;
            byte[] buffer = new byte[1];
            buffer[0] = wr;

            WriteProcessMemory((int)processHandle, where, buffer, buffer.Length, ref bytesWritten);
        }

        public void WriteInt(int where, int wr)
        {
            IntPtr processHandle = OpenProcess(PROCESS_VM_MAGIC, false, process.Id);

            int bytesWritten = 4;
            byte[] buffer = BitConverter.GetBytes(wr);

            WriteProcessMemory((int)processHandle, where, buffer, buffer.Length, ref bytesWritten);
        }

        public void WriteShort(int where, short wr)
        {
            IntPtr processHandle = OpenProcess(PROCESS_VM_MAGIC, false, process.Id);

            int bytesWritten = 2;
            byte[] buffer = BitConverter.GetBytes(wr);

            WriteProcessMemory((int)processHandle, where, buffer, buffer.Length, ref bytesWritten);
        }

        public void WriteUInt32(int where, uint wr)
        {
            IntPtr processHandle = OpenProcess(PROCESS_VM_MAGIC, false, process.Id);

            int bytesWritten = 4;
            byte[] buffer = BitConverter.GetBytes(wr);

            WriteProcessMemory((int)processHandle, where, buffer, buffer.Length, ref bytesWritten);
        }

        public string ReadString(int where, int count)
        {
            IntPtr processHandle = OpenProcess(PROCESS_VM_READ, false, process.Id);

            int bytesRead = count;
            byte[] buffer = new byte[count];

            ReadProcessMemory((int)processHandle, where, buffer, buffer.Length, ref bytesRead);

            return System.Text.Encoding.Default.GetString(buffer);
        }

        public string ReadString(int where)
        {
            List<byte> str = new List<byte>();

            int offset = where;
            byte x;

            do
            {
                x = ReadByte(offset);
                if (x != 0x0) str.Add(x);
                offset++;
            }
            while (x != 0x0);

            return System.Text.Encoding.Default.GetString(str.ToArray());
        }

        public void WriteString(int where, string wr)
        {
            IntPtr processHandle = OpenProcess(PROCESS_VM_MAGIC, false, process.Id);

            byte[] buffer = System.Text.Encoding.Default.GetBytes(wr);
            int bytesWritten = buffer.Length;

            WriteProcessMemory((int)processHandle, where, buffer, buffer.Length, ref bytesWritten);
        }

        public void WriteFile(int where, string fn)
        {
            byte[] buf = File.ReadAllBytes(fn);
            WriteArray(where, buf);
        }

    }
}
