.text
.global icoro_transfer, icoro_begin

/*
 * icoro_transfer: transfere o controle para uma corotina
 *
 * Parâmetros:
 *   - corotina corrente
 *   - a corotina a ativar
 *   - valor a ser passado para a corotina 
 *
 */
icoro_transfer:
  push	%ebp
  mov  %esp, %ebp

  mov  8(%ebp), %ecx    # obtem o descritor da corotina ativa
  mov  12(%ebp), %edx	# obtem o descritor da corotina a (re)ativar
  mov  16(%ebp), %eax   # valor para a corotina

  push  %ebx        	# salva os registradores da corotina ativa
  push  %edi        	# %eax, %ecx e %edx não precisam ser salvos!
  push  %esi        
  push  %ebp        

  call transfer		# coloca o endereço (%eip) do ponto de retorno na pilha

/* ponto de retorno quando o controle voltar */

  pop   %ebp		# restaura registradores salvos
  pop   %esi
  pop   %edi
  pop   %ebx
  mov   %ebp, %esp
  pop   %ebp
  ret

/* transfere o controle */
transfer:
  mov   %esp, (%ecx)	# salva o topo da pilha corrente
  mov  (%edx), %esp	# agora a pilha é a da corotina a reativar!
  ret

/*
 * icoro_begin: inicia a execução de uma corotina
 *
 * No fundo da pilha está o endereço do corpo da corotina
 * Deve colocar na pilha o parâmetro (em %eax) e o endereço de retorno para 
   finalização da corotina
 */
icoro_begin:
  pop  %ecx	        # pega o endereço do corpo da corotina no fundo da pilha

  push  %eax
  push $terminate	# coloca o endereço de finalização (acima do parâmetro)
  
  push %ecx		# entry_point do corpo da corotina
  ret

/*
 * terminate: finaliza a corotina
 *
 */
terminate:
  push %eax            # empilha o retorno do corpo da corotina
  call coro_end

  # não deve voltar a este ponto
