/* Address: ram:0005130a; name: FUN_ram_0005130a; body bytes: 36 */

void FUN_ram_0005130a(int param_1,int param_2)

{
  byte *pbVar1;
  byte *pbVar2;
  int iVar3;
  
  gp = 0x20004000;
  iVar3 = 0;
  do {
    pbVar1 = (byte *)(param_1 + iVar3);
    pbVar2 = (byte *)(param_2 + iVar3);
    iVar3 = iVar3 + 1;
    *pbVar1 = *pbVar2 ^ *pbVar1;
  } while (iVar3 != 0x10);
  return;
}

