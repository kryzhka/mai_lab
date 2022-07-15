//2*a*2->4*a
#include <stdio.h>
#include <stdlib.h>

typedef char tdata;

int i; char ch;

struct node;

typedef node * link;

struct node
{
    tdata data;
    link left, right;
} *tree;

void printtree(link t)
{
    static int l=0;
    l++;
    if(t)
    {
        printtree(t->right);
        for(i=0;i<l;i++)
            printf("    ");
        printf("\\__%c\n",t->data);
        printtree(t->left);
    }
    l--;
}


int isAN()
{
    return (ch>='a')&&(ch<='z')||(ch>='0')&&(ch<='9');
}

int isN(char c)
{
    return (c>='0')&&(c<='9');
}

link mknode(char c, link l, link r)
{
    link t=new node;
    t->data=c;
    t->left=l;
    t->right=r;
    return t;
}

link expr();

link fact()
{
    link t;
    scanf("%c",&ch);
    if(ch=='(')
    {
        t=expr();
		if(ch!=')')
            printf("ERROR: not )\n");
	}
    else if(isAN()) 
        t=mknode(ch,0,0);
	else 
        printf("ERROR: not AN\n");
    return t;
}

link term()
{
    link tm;
    int done;
    char ch1;
    tm=fact();
    done=0;
    while((ch!='\n')&&(!done))
    {
        scanf("%c",&ch);
    if((ch=='*')||(ch=='/'))
    {
        ch1=ch;
        tm=mknode(ch1,tm,fact());
    }
    else done=1;
   }
   return tm;
}

link expr()
{
    link ex;
    int done;
    char ch1;
    ex=term();
    done=0;
    while((ch!='\n')&&(!done))
    {
        if((ch=='+')||(ch=='-'))
        {
            ch1=ch;
            ex=mknode(ch1,ex,term());
        }
        else
            done=1;
    }
    return ex;
}

void tree2expr(link tree)
{
    if(tree)
    {
        if((tree->data=='+')||(tree->data=='-'))
            printf("(");
    tree2expr(tree->left);
    printf("%c",tree->data);
    tree2expr(tree->right);
    if((tree->data=='+')||(tree->data=='-'))
        printf(")");
    }
}

void  transtree(link tree)
{
    char c, cl, cr,r;
    if(tree)
    {
        if(tree->data=='*')
        {
            cl=tree->left->data;
            cr=tree->right->data;
           
            
            if((tree->left->data=='*')&&isN(tree->right->data))//1,2
            {
                if(isN(tree->left->left->data))//1
                {
                    c=(tree->left->left->data-'0')*(tree->right->data-'0');
                    if(c<10)
                    {
                        tree->right->data=c+'0';
                        tree->left=tree->left->right;
                        i=1;
                    }
                }
                else if(isN(tree->left->right->data))//2
                {
                    c=(tree->left->right->data-'0')*(tree->right->data-'0');
                    if(c<10)
                    {
                        tree->right->data=c+'0';
                        tree->left=tree->left->left;
                        i=1;
                    }
                }
            }
            else if((tree->right->data=='*')&&isN(tree->left->data))//3,4
            {

            }
            if(isN(cl)&&isN(cr))
            {
                c=(cl-'0')*(cr-'0');
                
                if(c<10)
                {
                    tree->data=c+'0';
                    tree->left=0;
                    tree->right=0;
                    i=1;
                }
            }
            
        }
        
        transtree(tree->left);
        transtree(tree->right);
    }
}

int main()
{
    // clrscr();
    printf("Input expression:\n");
    tree=expr();
    printtree(tree);
    printf("\n\n-----------------------\n\n");
    tree2expr(tree);
    i=1;
    while(i)
    {
        i=0;
        transtree(tree);
    }
    printf("\n\n-----------------------\n\n");
    printtree(tree);
    printf("\n\n-----------------------\n\n");
    tree2expr(tree);
    printf("\n\n-----------------------\n\n");
    return 0;
}
