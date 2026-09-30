/* Address: CODE:8864; name: FUN_CODE_8864; body bytes: 49 */

void FUN_CODE_8864(char *param_1)

{
  char cVar1;
  char cVar2;
  
  cVar2 = DAT_INTMEM_b3;
  FUN_CODE_109e();
  FUN_CODE_5078();
  FUN_CODE_691c(*param_1);
  cVar1 = DAT_INTMEM_b3;
  FUN_CODE_507b(DAT_INTMEM_b3);
  if (*param_1 != cVar2) {
    FUN_CODE_507d(cVar1 + '\x10');
    *param_1 = cVar2;
  }
  FUN_CODE_8e81();
  FUN_CODE_8f87();
  FUN_CODE_a595();
  FUN_CODE_5085();
  *param_1 = cVar2;
  return;
}

