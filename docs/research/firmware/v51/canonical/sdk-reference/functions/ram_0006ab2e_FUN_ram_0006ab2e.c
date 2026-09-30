/* Address: ram:0006ab2e; name: FUN_ram_0006ab2e; body bytes: 758 */

void FUN_ram_0006ab2e(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  gp = 0x20004000;
  cVar1 = *(char *)(param_1 + 2);
  switch(cVar1) {
  case '\0':
    if (*(char *)(param_1 + 1) == '\0') {
      iVar3 = tmos_memcmp(&DAT_ram_20001f28,&DAT_ram_20001b34,0x10);
      if ((iVar3 == 0) ||
         (iVar3 = tmos_memcmp(&DAT_ram_20001f38,&DAT_ram_20001b44,0x10), iVar3 == 0)) {
        FUN_ram_00042e5e(2,0x10,&DAT_ram_20001f28);
        FUN_ram_00042e5e(3,0x10,&DAT_ram_20001f38);
        FUN_ram_00042e10(DAT_ram_200019c4);
      }
      tmos_memcpy(&DAT_ram_20001f4c,param_1 + 3,6);
      DAT_ram_20001f20 = 1;
      tmos_set_event(DAT_ram_200019cc,1);
      uVar6 = DAT_ram_20001f20;
    }
    else {
      DAT_ram_20001f20 = 6;
      uVar6 = DAT_ram_20001f20;
    }
    break;
  case '\x01':
  case '\a':
  case '\b':
  case '\t':
  case '\n':
  case '\v':
  case '\f':
  case '\r':
  case '\x0e':
  case '\x0f':
  case '\x10':
  case '\x11':
  case '\x12':
  case '\x15':
  case '\x16':
  case '\x17':
  case '\x18':
  case '\x19':
  case '\x1a':
    goto switchD_ram_0006ab56_caseD_1;
  case '\x02':
    cVar1 = *(char *)(param_1 + 3);
    if (*(char *)(param_1 + 1) == '\0') {
      if (cVar1 == '\x02') {
        DAT_ram_20001f20 = DAT_ram_20001f20 & 0xffffff0f | 0x20;
        uVar2 = FUN_ram_00047750(0,0);
      }
      else if (cVar1 == '\x01') {
        uVar2 = FUN_ram_00047640();
      }
      else {
        uVar2 = FUN_ram_00047530(0,0);
      }
      *(undefined1 *)(param_1 + 1) = uVar2;
      gp = 0x20004000;
      return;
    }
    if (cVar1 == '\x02') {
      gp = 0x20004000;
      return;
    }
    DAT_ram_20001f20 = DAT_ram_20001f20 & 0xfffffff0 | 6;
    uVar6 = DAT_ram_20001f20;
    break;
  case '\x03':
  case '\x04':
    if (*(char *)(param_1 + 1) == '\0') {
      if (cVar1 == '\x03') {
        if ((char)DAT_ram_20001f18 < '\0') {
          DAT_ram_20001f18 = DAT_ram_20001f18 & 0x7f;
          tmos_set_event(DAT_ram_200019cc,2);
        }
        if ((DAT_ram_20001f20 & 0xf) == 4) {
          DAT_ram_20001f20 = DAT_ram_20001f20 & 0xfffffff0 | 5;
          uVar6 = DAT_ram_20001f20;
        }
        else {
          if ((DAT_ram_20001f20 & 0xf) == 2) {
            gp = 0x20004000;
            return;
          }
          DAT_ram_20001f20 = DAT_ram_20001f20 & 0xfffffff0 | 2;
          uVar6 = DAT_ram_20001f20;
        }
      }
      else {
        DAT_ram_20001f14 = 0;
        if ((DAT_ram_20001f20 & 0xf) != 5) goto LAB_ram_0006ad58;
        DAT_ram_20001f20 = DAT_ram_20001f20 & 0xfffffff0 | 4;
        uVar6 = DAT_ram_20001f20;
      }
    }
    else {
LAB_ram_0006ad0a:
      DAT_ram_20001f20 = DAT_ram_20001f20 & 0xfffffff0 | 6;
      uVar6 = DAT_ram_20001f20;
    }
    break;
  case '\x05':
    if (*(char *)(param_1 + 1) == '\0') {
      DAT_ram_20001f20 = DAT_ram_20001f20 & 0xfffffff0 | 4;
      FUN_ram_00069cb0(*(undefined1 *)(param_1 + 3),param_1 + 4,*(undefined2 *)(param_1 + 10),4);
      DAT_ram_20001f14 = 0;
      uVar6 = DAT_ram_20001f20;
    }
    else {
      if (*(char *)(param_1 + 1) != '1') goto LAB_ram_0006ad0a;
LAB_ram_0006ad58:
      DAT_ram_20001f14 = 0;
      DAT_ram_20001f20 = DAT_ram_20001f20 & 0xfffffff0 | 3;
      uVar6 = DAT_ram_20001f20;
    }
    break;
  case '\x06':
    FUN_ram_0006a4ec();
    uVar4 = DAT_ram_20001f20 & 0xf;
    uVar5 = DAT_ram_20001f20 & 0xfffffff0;
    DAT_ram_20001f20 = uVar5 | 3;
    uVar6 = DAT_ram_20001f20;
    if (uVar4 == 5) {
      DAT_ram_20001f20 = uVar5 | 2;
      uVar6 = DAT_ram_20001f20;
    }
    break;
  case '\x13':
  case '\x14':
    uVar6 = DAT_ram_20001f20 & 0xffffff0f;
    if (*(char *)(param_1 + 1) == '\0') {
      if (cVar1 == '\x13') {
        DAT_ram_20001f20 = uVar6 | 0x10;
        if ((char)DAT_ram_20001f53 < '\0') {
          DAT_ram_20001f53 = DAT_ram_20001f53 & 0x7f;
          tmos_set_event(DAT_ram_200019cc,4);
        }
      }
      else {
        DAT_ram_20001f20 = uVar6 | 0x20;
      }
    }
    else {
      DAT_ram_20001f20 = uVar6 | 0x30;
    }
    uVar6 = 0x1000000;
    goto LAB_ram_0006add4;
  case '\x1b':
  case '\x1c':
    uVar6 = DAT_ram_20001f20 & 0xfffff0ff;
    if (*(char *)(param_1 + 1) == '\0') {
      if (cVar1 == '\x1b') {
        DAT_ram_20001f20 = uVar6 | 0x100;
      }
      else {
        DAT_ram_20001f20 = uVar6 | 0x200;
      }
    }
    else {
      DAT_ram_20001f20 = uVar6 | 0x300;
    }
    uVar6 = 0x2000000;
LAB_ram_0006add4:
    uVar6 = uVar6 | DAT_ram_20001f20;
    break;
  default:
    return;
  }
  if ((DAT_ram_20001abc != (undefined4 *)0x0) && ((code *)*DAT_ram_20001abc != (code *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x0006abf4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*(code *)*DAT_ram_20001abc)(uVar6,param_1);
    return;
  }
switchD_ram_0006ab56_caseD_1:
  return;
}

