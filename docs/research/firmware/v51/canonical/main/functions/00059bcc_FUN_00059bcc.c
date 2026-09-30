/* Address: 00059bcc; name: FUN_00059bcc; body bytes: 72 */

void FUN_00059bcc(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_1ffe0074;
  do {
    puVar1 = puVar2;
    puVar2 = (undefined4 *)*puVar1;
  } while (puVar2 < param_1);
  if ((undefined4 *)(puVar1[1] + (int)puVar1) == param_1) {
    puVar1[1] = param_1[1] + puVar1[1];
    param_1 = puVar1;
  }
  if ((undefined4 *)(param_1[1] + (int)param_1) == puVar2) {
    if (puVar2 == DAT_1ffe0060) {
      *param_1 = DAT_1ffe0060;
      goto LAB_00059c08;
    }
    param_1[1] = puVar2[1] + param_1[1];
    puVar2 = *(undefined4 **)*puVar1;
  }
  *param_1 = puVar2;
LAB_00059c08:
  if (puVar1 != param_1) {
    *puVar1 = param_1;
  }
  return;
}

