/* Address: ram:000511d0; name: FUN_ram_000511d0; body bytes: 46 */

void FUN_ram_000511d0(int param_1,int param_2)

{
  byte *pbVar1;
  byte bVar2;
  uint uVar3;
  
  gp = 0x20004000;
  bVar2 = 0;
  uVar3 = 0xf;
  do {
    pbVar1 = (byte *)(param_1 + uVar3);
    *(byte *)(param_2 + uVar3) = bVar2 | *pbVar1 << 1;
    uVar3 = uVar3 - 1 & 0xff;
    bVar2 = *pbVar1 >> 7;
  } while (uVar3 != 0xff);
  return;
}

