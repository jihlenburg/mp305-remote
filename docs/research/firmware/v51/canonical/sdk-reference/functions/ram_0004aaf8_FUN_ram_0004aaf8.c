/* Address: ram:0004aaf8; name: FUN_ram_0004aaf8; body bytes: 150 */

undefined1 *
FUN_ram_0004aaf8(uint param_1,uint param_2,undefined4 param_3,int param_4,undefined2 *param_5)

{
  short sVar1;
  undefined2 uVar2;
  undefined1 *puVar3;
  int *piVar4;
  int iVar5;
  short sVar6;
  
  gp = 0x20004000;
  piVar4 = (int *)DAT_ram_20001a48;
  do {
    if (piVar4 == (int *)0x0) {
      return (undefined1 *)0x0;
    }
    puVar3 = (undefined1 *)piVar4[2];
    sVar1 = *(short *)(piVar4 + 1);
    uVar2 = *(undefined2 *)(puVar3 + 10);
    for (sVar6 = 0; sVar6 != sVar1; sVar6 = sVar6 + 1) {
      if (((param_1 <= *(ushort *)(puVar3 + 10)) && (*(ushort *)(puVar3 + 10) <= param_2)) &&
         ((param_4 == 0 ||
          (iVar5 = ATT_CompareUUID(*(undefined4 *)(puVar3 + 4),*puVar3,param_3,param_4), iVar5 != 0)
          ))) {
        if (param_5 == (undefined2 *)0x0) {
          gp = 0x20004000;
          return puVar3;
        }
        *param_5 = uVar2;
        gp = 0x20004000;
        return puVar3;
      }
      puVar3 = puVar3 + 0x10;
    }
    piVar4 = (int *)*piVar4;
  } while( true );
}

