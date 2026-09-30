/* Address: ram:0006b7f6; name: GAPRole_SetPathLossReporting; body bytes: 4 */

void GAPRole_SetPathLossReporting(undefined2 *param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0006808c(*param_1,*(undefined1 *)((int)param_1 + 3),*(undefined1 *)(param_1 + 1),
                           *(undefined1 *)((int)param_1 + 5),*(undefined1 *)(param_1 + 2),param_1[3]
                          );
  if (iVar1 == 0) {
    FUN_ram_0006814e(*param_1,*(undefined1 *)(param_1 + 4));
    return;
  }
  return;
}

