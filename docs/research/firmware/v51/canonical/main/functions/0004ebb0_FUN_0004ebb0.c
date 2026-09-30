/* Address: 0004ebb0; name: FUN_0004ebb0; body bytes: 328 */

void FUN_0004ebb0(int param_1,int param_2,undefined2 param_3,undefined2 param_4,undefined2 *param_5)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined1 auStack_78 [88];
  
  *(ushort *)(param_1 + 0x2a) = *(ushort *)(param_1 + 0x2a) | 8;
  *(undefined2 *)(param_1 + 0x28) = param_3;
  iVar1 = FUN_0004c924(param_1,param_2,*(undefined1 *)(param_5 + 4));
  *(undefined2 *)(param_1 + 0x28) = param_4;
  iVar2 = FUN_0004c924(param_1,param_2,*(undefined1 *)(param_5 + 4));
  *(ushort *)(param_1 + 0x2a) = *(ushort *)(param_1 + 0x2a) & 0xfff7;
  if ((iVar1 != iVar2) || (iVar1 = FUN_000402f4(iVar1,iVar2), iVar1 == 0)) {
    *(undefined2 *)(param_1 + 0x28) = param_3;
    iVar1 = FUN_0004c924(param_1,param_2,*(undefined1 *)(param_5 + 4));
    *(undefined2 *)(param_1 + 0x28) = param_4;
    puVar3 = (undefined4 *)FUN_00037c5c(param_1,param_2);
    FUN_00050ef2(*puVar3,*(undefined1 *)(param_5 + 4),iVar1);
    FUN_0004dedc(param_1,*(undefined4 *)(param_5 + 2),*(undefined1 *)(param_5 + 4));
    if ((*(char *)(param_5 + 4) == '\f') && ((iVar1 == 0x7fff || (iVar2 == 0x7fff)))) {
      iVar4 = FUN_0004ccf8(param_1);
      iVar4 = iVar4 / 2;
      iVar5 = FUN_0004bbec(param_1);
      iVar5 = iVar5 / 2;
      if ((iVar1 == 0x7fff) && (iVar1 = iVar5 + 1, iVar4 + 1 < iVar1)) {
        iVar1 = iVar4 + 1;
      }
      if (iVar2 == 0x7fff) {
        if (iVar4 + 1 < iVar5 + 1) {
          iVar5 = iVar4;
        }
        iVar2 = iVar5 + 1;
      }
    }
    piVar6 = (int *)FUN_0004a162(&DAT_2003a438);
    if (piVar6 == (int *)0x0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    *piVar6 = param_1;
    piVar6[3] = iVar1;
    piVar6[4] = iVar2;
    *(undefined1 *)(piVar6 + 1) = *(undefined1 *)(param_5 + 4);
    piVar6[2] = param_2;
    FUN_0003c9f8(auStack_78);
    FUN_0003cb2a(auStack_78,piVar6);
    FUN_0003cafa(auStack_78,0x635a1);
    FUN_0003cb12(auStack_78,0x63781);
    FUN_0003cadc(auStack_78,0x636d9);
    FUN_0003cb1e(auStack_78,0,0xff);
    FUN_0003caea(auStack_78,*param_5);
    FUN_0003cae0(auStack_78,param_5[1]);
    FUN_0003cafe(auStack_78,*(undefined4 *)(param_5 + 6));
    FUN_0003caee(auStack_78,0);
    FUN_0003cb1a(auStack_78,*(undefined4 *)(param_5 + 8));
    FUN_0003cb6c(auStack_78);
  }
  return;
}

