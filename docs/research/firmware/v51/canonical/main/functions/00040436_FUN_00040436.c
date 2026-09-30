/* Address: 00040436; name: FUN_00040436; body bytes: 36 */

uint FUN_00040436(undefined4 param_1,undefined4 param_2)

{
  byte bVar1;
  undefined4 local_8;
  
  bVar1 = (byte)((uint)param_1 >> 8);
  local_8._0_1_ = (byte)param_2;
  local_8 = CONCAT31((int3)((uint)param_2 >> 8),
                     (char)((uint)((int)(short)(ushort)(byte)local_8 *
                                   (int)(short)(0xff - (ushort)bVar1) +
                                  (int)(short)((ushort)param_1 & 0xff) * (int)(short)(ushort)bVar1)
                           >> 8));
  return local_8 & 0xffff;
}

