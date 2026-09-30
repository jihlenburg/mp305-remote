/* Address: ram:000511a8; name: FUN_ram_000511a8; body bytes: 40 */

void FUN_ram_000511a8(int param_1,int param_2,int param_3)

{
  byte *pbVar1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  gp = 0x20004000;
  iVar2 = 0;
  do {
    pbVar1 = (byte *)(param_1 + iVar2);
    pbVar4 = (byte *)(param_2 + iVar2);
    pbVar3 = (byte *)(param_3 + iVar2);
    iVar2 = iVar2 + 1;
    *pbVar3 = *pbVar1 ^ *pbVar4;
  } while (iVar2 != 0x10);
  return;
}

