/* Address: ram:20000750; name: FUN_ram_20000750; body bytes: 1 */

undefined4 FUN_ram_20000750(int param_1)

{
  byte bVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  short sVar6;
  
  gp = 0x20004000;
  if (((DAT_ram_20001e7c & 1) == 0) &&
     (puVar2 = (undefined4 *)FUN_ram_00057bbc(0xff52), puVar2 != (undefined4 *)0x0)) {
    *(ushort *)((int)puVar2 + 10) = (ushort)*(byte *)((int)puVar2 + 10);
    if (*(int *)(param_1 + 0x120) == 0) {
      *(undefined4 **)(param_1 + 0x120) = puVar2;
      *(undefined4 **)(param_1 + 0x124) = puVar2;
      sVar6 = 1;
    }
    else {
      **(undefined4 **)(param_1 + 0x124) = puVar2;
      *(undefined4 **)(param_1 + 0x124) = puVar2;
      sVar6 = *(short *)(param_1 + 0x40) + 1;
    }
    *(short *)(param_1 + 0x40) = sVar6;
    *puVar2 = 0;
    bVar1 = *(byte *)(param_1 + 0x16);
    puVar5 = (undefined4 *)puVar2[1];
    *(ushort *)(puVar2 + 3) = (ushort)bVar1;
    *(undefined1 *)(puVar2 + 2) = *(undefined1 *)(param_1 + 0xd);
    *(undefined1 *)((int)puVar2 + 9) = 1;
    uVar3 = bVar1 + 0x21 >> 5;
    puVar2 = DAT_ram_20001eac;
    while( true ) {
      uVar3 = uVar3 - 1 & 0xff;
      *puVar5 = *puVar2;
      puVar5[1] = puVar2[1];
      puVar5[2] = puVar2[2];
      puVar5[3] = puVar2[3];
      puVar5[4] = puVar2[4];
      puVar5[5] = puVar2[5];
      puVar5[6] = puVar2[6];
      puVar5[7] = puVar2[7];
      if (uVar3 == 0) break;
      puVar5 = puVar5 + 8;
      puVar2 = puVar2 + 8;
    }
    DAT_ram_20001d68 = DAT_ram_20001d68 + 1;
    uVar4 = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x12) = 0;
    uVar4 = 1;
    *(byte *)(param_1 + 0xc) = *(byte *)(param_1 + 0xc) ^ 4;
  }
  return uVar4;
}

