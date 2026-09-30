/* Address: ram:00041d8e; name: FUN_ram_00041d8e; body bytes: 34 */

byte * FUN_ram_00041d8e(uint param_1,uint param_2)

{
  byte *pbVar1;
  
  gp = 0x20004000;
  for (pbVar1 = DAT_ram_20001bb8;
      (pbVar1 != (byte *)0x0 && ((*(ushort *)(pbVar1 + 2) != param_2 || (*pbVar1 != param_1))));
      pbVar1 = *(byte **)(pbVar1 + 0xc)) {
  }
  return pbVar1;
}

