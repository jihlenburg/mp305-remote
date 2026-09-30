/* Address: CODE:ae53; name: FUN_CODE_ae53; body bytes: 38 */

void FUN_CODE_ae53(char param_1)

{
  char *pcVar1;
  undefined1 uStackX_0;
  undefined1 in_stack_000000ff;
  
  for (pcVar1 = (char *)CONCAT11(uStackX_0,in_stack_000000ff);
      (*pcVar1 != '\0' || (pcVar1[1] != '\0')); pcVar1 = pcVar1 + 3) {
    if (pcVar1[2] == param_1) goto LAB_CODE_ae63;
  }
  pcVar1 = pcVar1 + 2;
LAB_CODE_ae63:
                    /* WARNING: Could not recover jumptable at 0xae6d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)pcVar1)();
  return;
}

