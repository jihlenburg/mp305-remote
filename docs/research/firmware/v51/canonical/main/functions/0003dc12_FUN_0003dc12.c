/* Address: 0003dc12; name: FUN_0003dc12; body bytes: 40 */

undefined4 FUN_0003dc12(int *param_1,int *param_2)

{
  if ((((*param_1 <= param_2[2]) && (*param_2 <= param_1[2])) && (param_1[1] <= param_2[3])) &&
     (param_2[1] <= param_1[3])) {
    return 1;
  }
  return 0;
}

