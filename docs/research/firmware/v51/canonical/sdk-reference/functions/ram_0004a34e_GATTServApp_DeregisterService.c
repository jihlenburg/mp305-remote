/* Address: ram:0004a34e; name: GATTServApp_DeregisterService; body bytes: 92 */

int GATTServApp_DeregisterService(uint param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined1 auStack_18 [4];
  undefined4 uStack_14;
  
  gp = 0x20004000;
  puVar1 = (undefined4 *)0x0;
  puVar4 = DAT_ram_20001a54;
  do {
    puVar5 = puVar4;
    puVar3 = puVar1;
    if (puVar5 == (undefined4 *)0x0) {
      return 1;
    }
    puVar4 = (undefined4 *)*puVar5;
    puVar1 = puVar5;
  } while (*(ushort *)(puVar5 + 1) != param_1);
  if (puVar3 != (undefined4 *)0x0) {
    *puVar3 = puVar4;
    puVar4 = DAT_ram_20001a54;
  }
  DAT_ram_20001a54 = puVar4;
  FUN_ram_20000104(puVar5);
  iVar2 = FUN_ram_0004a2f4(param_1,auStack_18);
  if ((iVar2 == 0) && (param_2 != (undefined4 *)0x0)) {
    *param_2 = uStack_14;
  }
  return iVar2;
}

