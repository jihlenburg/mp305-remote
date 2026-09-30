/* Address: ram:0004201e; name: FUN_ram_0004201e; body bytes: 240 */

undefined4 FUN_ram_0004201e(int param_1,int param_2,uint param_3,undefined1 *param_4,int param_5)

{
  int iVar1;
  uint uVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  int *piVar6;
  
  gp = 0x20004000;
  if ((param_1 != 0) && (param_3 < 0xa6f63c81)) {
    uVar2 = 0;
    do {
      if (*(int *)(DAT_ram_20001bf8 + uVar2 * 0xc) == 0) {
        puVar3 = (undefined1 *)FUN_ram_20000040(0x10,0xff00);
        if (puVar3 == (undefined1 *)0x0) {
          if (DAT_ram_20001bec != (code *)0x0) {
            (*DAT_ram_20001bec)(4,0);
          }
        }
        else {
          puVar4 = DAT_ram_20001bb8;
          puVar5 = puVar3;
          if (DAT_ram_20001bb8 != (undefined1 *)0x0) {
            do {
              puVar5 = puVar4;
              puVar4 = *(undefined1 **)(puVar5 + 0xc);
            } while (puVar4 != (undefined1 *)0x0);
            *(undefined1 **)(puVar5 + 0xc) = puVar3;
            puVar5 = DAT_ram_20001bb8;
          }
          DAT_ram_20001bb8 = puVar5;
          *puVar3 = 0;
          iVar1 = DAT_ram_20001bf8;
          *(undefined4 *)(puVar3 + 0xc) = 0;
          *(uint *)(puVar3 + 8) = param_3;
          *(short *)(puVar3 + 2) = (short)(1 << (uVar2 & 0x1f));
          *(int *)(puVar3 + 4) = param_5;
          piVar6 = (int *)(iVar1 + uVar2 * 0xc);
          *piVar6 = param_1;
          piVar6[1] = param_2;
          piVar6[2] = param_5;
          if (param_4 != (undefined1 *)0x0) {
            *param_4 = (char)uVar2;
          }
        }
        gp = 0x20004000;
        return 0;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 != 0x10);
    return 8;
  }
  return 2;
}

