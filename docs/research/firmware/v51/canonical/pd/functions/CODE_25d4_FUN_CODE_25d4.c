/* Address: CODE:25d4; name: FUN_CODE_25d4; body bytes: 41 */

void FUN_CODE_25d4(char param_1,char param_2)

{
  byte bVar1;
  undefined1 *puVar2;
  
  DAT_EXTMEM_04aa = param_2;
  DAT_EXTMEM_04ab = param_1;
  if (param_1 != param_2) {
    bVar1 = param_1 - 1;
    if ((bVar1 < 7) << 7 < '\0') {
      puVar2 = &LAB_CODE_25f4;
      if (CARRY1(bVar1,bVar1)) {
        puVar2 = (undefined1 *)0x26f4;
      }
                    /* WARNING: Could not recover jumptable at 0x25f3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*(code *)(puVar2 + bVar1 * '\x02'))();
      return;
    }
    FUN_CODE_a6f1(param_1);
  }
  return;
}

