/* Address: ram:00067198; name: FUN_ram_00067198; body bytes: 426 */

undefined4 FUN_ram_00067198(uint param_1,uint param_2,int param_3,int param_4,int param_5)

{
  undefined1 uVar1;
  int *piVar2;
  short sVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  gp = 0x20004000;
  if ((DAT_ram_20001db4 == 0) || (-1 < *(int *)(DAT_ram_20001db4 + 0x54) << 5)) {
    if ((param_1 & 1) == 0) {
      piVar2 = DAT_ram_20001db8;
      if (param_2 == 0) {
        for (; piVar2 != (int *)0x0; piVar2 = (int *)*piVar2) {
          FUN_ram_0005501c(piVar2);
        }
      }
      else if (DAT_ram_20001db4 != 0) {
        FUN_ram_0005501c(DAT_ram_20001db4);
      }
      uVar4 = 0;
    }
    else {
      if (param_2 != 0) {
        while (param_2 = param_2 - 1 & 0xff, param_2 != 0xff) {
          iVar6 = FUN_ram_00054de4(*(undefined1 *)(param_3 + param_2));
          if (iVar6 == 0) {
            if (DAT_ram_20001db4 == 0) {
              gp = 0x20004000;
              return 0x42;
            }
            goto LAB_ram_000671d4;
          }
          if (((*(uint *)(iVar6 + 0x54) & 0x3000000) != 0) ||
             (((*(char *)(iVar6 + 0x5f) == '\x02' || (*(char *)(iVar6 + 0x5f) == '\x05')) &&
              (*(short *)(iVar6 + 0x1e) == 0)))) goto LAB_ram_000671d4;
          if (*(char *)(iVar6 + 0x35) == '\x01') {
            iVar7 = iVar6 + 0x58;
            iVar5 = tmos_isbufset(iVar7,0,6);
            if (iVar5 == 1) {
              tmos_memcpy(iVar7,&DAT_ram_20001e3e,6);
            }
            iVar5 = tmos_isbufset(iVar7,0,6);
            if (iVar5 == 1) break;
          }
          if ((*(char *)(iVar6 + 0xe) == '\x01') && (0x80 < *(ushort *)(param_2 * 2 + param_4)))
          break;
          if (DAT_ram_20001dc8 != (code *)0x0) {
            *(undefined2 *)(iVar6 + 0x6c) = *(undefined2 *)(param_4 + param_2 * 2);
            uVar1 = *(undefined1 *)(param_2 + param_5);
            *(undefined2 *)(iVar6 + 0x6e) = 0;
            *(undefined1 *)(iVar6 + 0x69) = uVar1;
            sVar3 = FUN_ram_000428ec(1,200);
            *(ushort *)(iVar6 + 0x6a) = *(short *)(iVar6 + 0x6a) + 1U & 0xf | sVar3 << 4;
                    /* WARNING: Could not recover jumptable at 0x000672c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
            uVar4 = (*DAT_ram_20001dc8)(*(undefined1 *)(param_3 + param_2));
            return uVar4;
          }
        }
      }
      uVar4 = 0x12;
    }
  }
  else {
LAB_ram_000671d4:
    uVar4 = 0xc;
  }
  return uVar4;
}

