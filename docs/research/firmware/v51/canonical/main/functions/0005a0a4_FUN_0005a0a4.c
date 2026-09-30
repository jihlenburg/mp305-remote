/* Address: 0005a0a4; name: FUN_0005a0a4; body bytes: 232 */

void FUN_0005a0a4(int *param_1,int *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  
  if (param_1 == (int *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  while( true ) {
    if ((param_2 != (int *)0x0) && (*(char *)((int)param_2 + 0xc) != '\x01')) goto LAB_0005a186;
    if ((int *)*param_1 == param_2) goto LAB_0005a182;
    iVar2 = param_3[1];
    if ((int *)iVar2 != param_2) {
      if (*(char *)(iVar2 + 0xc) == '\0') {
        *(undefined1 *)(iVar2 + 0xc) = 1;
        *(undefined1 *)(param_3 + 3) = 0;
        FUN_0005a244(param_1,param_3);
        iVar2 = param_3[1];
      }
      iVar1 = *(int *)(iVar2 + 4);
      if ((iVar1 == 0) || (*(char *)(iVar1 + 0xc) == '\x01')) {
        if ((*(int *)(iVar2 + 8) == 0) || (*(char *)(*(int *)(iVar2 + 8) + 0xc) == '\x01'))
        goto LAB_0005a150;
        if ((iVar1 == 0) || (*(char *)(iVar1 + 0xc) == '\x01')) {
          *(undefined1 *)(*(int *)(iVar2 + 8) + 0xc) = 1;
          *(undefined1 *)(iVar2 + 0xc) = 0;
          FUN_0005a21a(param_1);
          iVar2 = param_3[1];
        }
      }
      *(undefined1 *)(iVar2 + 0xc) = *(undefined1 *)(param_3 + 3);
      *(undefined1 *)(param_3 + 3) = 1;
      *(undefined1 *)(*(int *)(iVar2 + 4) + 0xc) = 1;
      FUN_0005a244(param_1,param_3);
      goto LAB_0005a178;
    }
    iVar2 = param_3[2];
    if (*(char *)(iVar2 + 0xc) == '\0') {
      *(undefined1 *)(iVar2 + 0xc) = 1;
      *(undefined1 *)(param_3 + 3) = 0;
      FUN_0005a21a(param_1,param_3);
      iVar2 = param_3[2];
    }
    if ((*(int *)(iVar2 + 4) != 0) && (*(char *)(*(int *)(iVar2 + 4) + 0xc) != '\x01')) break;
    if ((*(int *)(iVar2 + 8) != 0) && (*(char *)(*(int *)(iVar2 + 8) + 0xc) != '\x01'))
    goto LAB_0005a10c;
LAB_0005a150:
    *(undefined1 *)(iVar2 + 0xc) = 0;
    param_2 = param_3;
    param_3 = (int *)*param_3;
  }
  if ((*(int *)(iVar2 + 8) == 0) || (*(char *)(*(int *)(iVar2 + 8) + 0xc) == '\x01')) {
    *(undefined1 *)(*(int *)(iVar2 + 4) + 0xc) = 1;
    *(undefined1 *)(iVar2 + 0xc) = 0;
    FUN_0005a244(param_1);
    iVar2 = param_3[2];
  }
LAB_0005a10c:
  *(undefined1 *)(iVar2 + 0xc) = *(undefined1 *)(param_3 + 3);
  *(undefined1 *)(param_3 + 3) = 1;
  *(undefined1 *)(*(int *)(iVar2 + 8) + 0xc) = 1;
  FUN_0005a21a(param_1,param_3);
LAB_0005a178:
  param_2 = (int *)*param_1;
LAB_0005a182:
  if (param_2 != (int *)0x0) {
LAB_0005a186:
    *(undefined1 *)((int)param_2 + 0xc) = 1;
  }
  return;
}

