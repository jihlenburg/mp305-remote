/* Address: ram:000431e0; name: FUN_ram_000431e0; body bytes: 148 */

byte FUN_ram_000431e0(int param_1,char *param_2)

{
  byte bVar1;
  uint uVar2;
  byte bVar3;
  int iVar4;
  byte *pbVar5;
  char cVar6;
  byte *pbVar7;
  
  gp = 0x20004000;
  uVar2 = (uint)*(ushort *)(param_1 + 6);
  if (uVar2 == 0) {
    bVar3 = 1;
  }
  else {
    pbVar7 = *(byte **)(param_1 + 8);
    bVar1 = *pbVar7;
    cVar6 = '\0';
    if ((char)bVar1 < '\0') {
      if (uVar2 < 0xd) {
        gp = 0x20004000;
        return 1;
      }
      uVar2 = uVar2 - 0xc & 0xffff;
      iVar4 = FUN_ram_0004f2fa(*(undefined2 *)(param_1 + 2),1,pbVar7,uVar2,pbVar7 + uVar2);
      cVar6 = (iVar4 != 0) + '\x01';
    }
    bVar3 = bVar1 >> 6 & 1;
    *param_2 = cVar6;
    param_2[1] = bVar3;
    param_2[2] = bVar1 & 0x3f;
    *(short *)(param_2 + 4) = (short)((uVar2 - 1) * 0x10000 >> 0x10);
    pbVar5 = (byte *)0x0;
    if ((uVar2 - 1 & 0xffff) != 0) {
      pbVar5 = pbVar7 + 1;
    }
    *(byte **)(param_2 + 8) = pbVar5;
    if (cVar6 != '\x02') {
      bVar3 = 0;
    }
  }
  return bVar3;
}

