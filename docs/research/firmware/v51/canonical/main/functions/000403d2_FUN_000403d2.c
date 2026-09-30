/* Address: 000403d2; name: FUN_000403d2; body bytes: 100 */

uint FUN_000403d2(undefined4 param_1,undefined4 param_2,short param_3)

{
  short sVar1;
  undefined4 local_14;
  
  sVar1 = 0xff - param_3;
  local_14 = CONCAT31((uint3)((uint)(((int)(short)(ushort)(byte)((uint)param_1 >> 8) * (int)param_3
                                     + (int)(short)(ushort)(byte)((uint)param_2 >> 8) * (int)sVar1)
                                    * 0x8081) >> 0x17),
                      (char)((uint)(((int)(short)((ushort)param_1 & 0xff) * (int)param_3 +
                                    (int)(short)((ushort)param_2 & 0xff) * (int)sVar1) * 0x8081) >>
                            0x17)) & 0xffff;
  return local_14 |
         ((((int)(short)(ushort)(byte)((uint)param_1 >> 0x10) * (int)param_3 +
           (int)(short)(ushort)(byte)((uint)param_2 >> 0x10) * (int)sVar1) * 0x8081 & 0x7fffffffU)
         >> 0x17) << 0x10;
}

