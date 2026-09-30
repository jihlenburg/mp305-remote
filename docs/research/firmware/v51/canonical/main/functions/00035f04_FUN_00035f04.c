/* Address: 00035f04; name: FUN_00035f04; body bytes: 54 */

undefined4 FUN_00035f04(undefined4 *param_1)

{
  int iVar1;
  
  if ((int)((uint)*(byte *)(param_1 + 6) << 0x1d) < 0) {
switchD_00035f2e_caseD_13:
  }
  else {
    if ((*(short *)(param_1 + 2) == 0x28) || (*(short *)(param_1 + 2) == 0x29)) {
switchD_00035f2e_caseD_14:
      return 1;
    }
    iVar1 = FUN_0004cd84(*param_1,0x4000);
    if (iVar1 != 0) {
      switch(*(undefined2 *)(param_1 + 2)) {
      case 0x13:
      case 0x17:
      case 0x18:
      case 0x19:
      case 0x1a:
      case 0x1b:
      case 0x1c:
      case 0x1d:
      case 0x1e:
      case 0x1f:
      case 0x22:
      case 0x26:
      case 0x27:
      case 0x28:
      case 0x29:
      case 0x2e:
      case 0x2f:
      case 0x31:
        goto switchD_00035f2e_caseD_13;
      default:
        goto switchD_00035f2e_caseD_14;
      }
    }
  }
  return 0;
}

