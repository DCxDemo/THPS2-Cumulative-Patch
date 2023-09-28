using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace thps2patch
{
    class MainPatch
    {
        Options op;

        public MainPatch(Options options)
        {
            op = options;
        }

        LevelPatch lp;
        LevelPatch up;

        public void Patch()
        {
            lp = new LevelPatch(".\\patch\\levelpatch.ini", op.Game);
            up = new LevelPatch(".\\patch\\userpatch.ini", op.Game);

            Mem mem = new Mem();

            bool foundTH2 = false;

            //loop until found THawk2 process
            while (!foundTH2)
            {
                try
                {
                    mem = new Mem("THawk2");
                    foundTH2 = true;
                }
                catch
                {
                    foundTH2 = false;
                }

               System.Threading.Thread.Sleep(100);
            }

            lp.Patch(op.ExeName);

            if (op.UserPatch)
                up.Patch(op.ExeName);
        }
    }
}