/* Address: ram:200002b4; name: tmos_isbufset; body bytes: 34 */

undefined4 tmos_isbufset(byte *param_1,uint param_2,int param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  
  gp = 0x20004000;
  if (param_1 == (byte *)0x0) {
    return 0;
  }
  if (param_3 != 0) {
    pbVar2 = param_1;
    while (pbVar1 = pbVar2 + 1, *pbVar2 == param_2) {
      pbVar2 = pbVar1;
      if (pbVar1 == param_1 + param_3) {
        return 1;
      }
    }
  }
  return 0;
}

