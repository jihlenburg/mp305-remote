/* Address: ram:00055d9e; name: FUN_ram_00055d9e; body bytes: 52 */

void FUN_ram_00055d9e(int param_1)

{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  
  gp = 0x20004000;
  pbVar3 = *(byte **)(param_1 + 0x114);
  bVar2 = 0xff;
  bVar1 = *pbVar3;
  *(byte *)(param_1 + 0xd) = bVar1 & 3;
  if ((bVar1 & 3) == 3) {
    bVar2 = pbVar3[2];
  }
  *(byte *)(param_1 + 0x17) = bVar2;
  *(byte *)(param_1 + 0x12) = *pbVar3 & 0x10;
  *(byte *)(param_1 + 0x16) = pbVar3[1];
  return;
}

