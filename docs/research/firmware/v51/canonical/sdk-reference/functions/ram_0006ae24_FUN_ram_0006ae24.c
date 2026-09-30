/* Address: ram:0006ae24; name: FUN_ram_0006ae24; body bytes: 98 */

void FUN_ram_0006ae24(char *param_1)

{
  gp = 0x20004000;
  if (*param_1 != -0x6f) {
    if (*param_1 != -0x30) {
      return;
    }
    FUN_ram_0006ab2e();
    return;
  }
  if ((param_1[1] == '\x0e') && (*(short *)(param_1 + 4) == 0x1405)) {
    if ((*(char *)(*(int *)(param_1 + 8) + 3) != '\x7f') &&
       ((DAT_ram_20001abc != 0 && (*(code **)(DAT_ram_20001abc + 4) != (code *)0x0)))) {
                    /* WARNING: Could not recover jumptable at 0x0006ae7e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(DAT_ram_20001abc + 4))(*(undefined2 *)(*(int *)(param_1 + 8) + 1));
      return;
    }
  }
  return;
}

