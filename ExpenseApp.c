#include<stdio.h>

#define SIZE 1000

//user structure
struct User
{
    int usr_id;
    char usr_name[30];
    float amt_spent;
};
struct User user[SIZE];

//expense structure
struct Expense
{
    int exp_id;
    float exp_amt;
    struct User *who_paid;
    int how_many_share;
    struct User *who_share[4];
};
struct Expense expense[SIZE];

//count of user and expense
int exp_count=0;
int usr_count=0;

//display expenses
int display_exp()
{
    printf("\nExpenses recorded are:-\n");
    for(int i=0;i<=exp_count;i++)
        printf("%d  %0.2f  %d  %d \n", expense[i].exp_id, expense[i].exp_amt, expense[i].how_many_share, expense[i].who_paid->usr_id);
    return 0;
}

//To check user id entered is valid. 
int valid_usr_id(int usrid)
{
    //binary search
    int flag=-1,low,high,mid;
    low=0,high=usr_count;
    while(low<=high && flag==-1)
    {
        mid=(low+high)/2;
        if(usrid == user[mid].usr_id)
        {
            flag=mid;
        }
        else if(usrid > user[mid].usr_id)
            low=mid+1;
        else if(usrid < user[mid].usr_id)
            high=mid-1;
    }
    return flag;
}

//To check expense id entered is valid.
int valid_exp_id(int expid)
{
    //binary search
    int flag=-1,low,high,mid;
    low=0,high=exp_count;
    while(low<=high && flag==-1)
    {
        mid=(low+high)/2;
        if(expid == expense[mid].exp_id)
        {
            flag=mid;
        }
        else if(expid > expense[mid].exp_id)
            low=mid+1;
        else if(expid < expense[mid].exp_id)
            high=mid-1;
    }
    return flag;
}

//add user function
void add_user(int usr_count)
{
    int userid=0,flag=-1,i=0;
    int n,t_usr_id,t_usr_name[30];
    float t_amt_spent;

    while(userid<1 || userid>1000)
    {
        printf("(Choose a user id from 1 to 1000)\n");
        printf("Enter a 3 digit user id: ");
        scanf("%d",&userid);
        flag = valid_usr_id(userid)+1;
        if(flag)
        {
            printf("User id already taken!!\n\n");
            userid=0;
        }
    }
    user[usr_count].usr_id=userid;
    printf("\nEnter your user name: ");
    scanf("%s",&user[usr_count].usr_name);

    printf("\nUser added succesfully! :)\n");

    //sorting based on user id
    struct User temp;
    for(int j=1;j<=usr_count;j++)
    {
        temp = user[j];
        n = j-1;
        while(temp.usr_id < user[n].usr_id && n>=0)
        {
            user[n+1] = user[n];
            while(i <= exp_count)
            {
                if(expense[i].who_paid->usr_id==user[n].usr_id)
                {
                    expense[i].who_paid->usr_id=user[n+1].usr_id;
                    for(int count=0;count<expense[i].how_many_share;count++)
                    {
                        if(expense[i].who_share[count]->usr_id==user[n].usr_id)
                        {
                            expense[i].who_share[count]->usr_id=user[n+1].usr_id;
                        }
                    }
                    i++;
                }
                else
                {    
                    i++;
                    flag=0;
                }
            }
            n--;
        }
        user[n+1]=temp;
    }
}

//add expense function
int add_expense(int exp_count)
{
    int expid=0,low,high,mid,flag=0,payerid,how_many_share=-1,flag2=0,paidfor=0,k=0,i,n;
    while (expid<1 || expid>1000)
    {
        printf("\n(Enter an exp id from 1 to 1000)");
        printf("\nEnter expense id: ");
        scanf("%d",&expid);
        flag=valid_exp_id(expid)+1;
        if(flag)
        {
            printf("\nExpense id already exist!!\n");
            expid=0;
        }
    }
    printf("\nEnter expense amount: ");
    scanf("%f",&expense[exp_count].exp_amt);

    printf("\nEnter payer user id: ");
    scanf("%d",&payerid);
    k=valid_usr_id(payerid)+1;
    if(k>0)
    {
        printf("Valid payer id! :)\n");
        expense[exp_count].who_paid = &user[k-1];
        user[k-1].amt_spent+=expense[exp_count].exp_amt;               //amount spent updated
    }
    else
    {
        printf("\nError!!  :(\n");
        add_expense(exp_count);
    }

    expense[exp_count].exp_id = expid;
    while(how_many_share<0 || how_many_share>4)
    {
        printf("\nEnter the no of people who share the expense (Max 4): \n");
        scanf("%d",&how_many_share);
        expense[exp_count].how_many_share=how_many_share;
    }

    //if you dont share exp with anyone
    if(how_many_share==0)
    {
        expense[exp_count].who_share[0] = &user[k-1];
    }
    else
    {
        while(flag2!=1)
        {

            for(i=0;i<how_many_share;i++)
            {
                flag2=0;
                printf("\nEnter %d user id that shares the expense: ",i+1);
                scanf("%d",&paidfor);
                k=valid_usr_id(paidfor)+1;
                if(k)
                {
                    flag2=1;
                    expense[exp_count].who_share[i] = &user[k-1];
                }
                else
                    printf("\nInavlid Input!!\n");
            }
        }
    }

    printf("\nRecorded expenses!! :)\n");

    //sorting based on exp id
    //insertion sort
    struct Expense temp;
    for(int j=1;j<exp_count;j++)
    {
        temp = expense[j];
        n = j-1;
        while(n>=0 && expense[n].exp_id > temp.exp_id)
        {
            expense[n+1]=expense[n];
            n--;
        }
        expense[n+1]=temp;
    }

    return 0;
}

//function to delete expense
int delete_exp(int usrid)
{
    int expid,flag=0,i=0,j,limit,k,exit=0,sharers;
    printf("\nEnter expense id: ");
    scanf("%d",&expid);
    limit=exp_count+1;
    while(i<limit && flag==0)
    {
        if(expense[i].exp_id==expid)
        {
            sharers=expense[i].how_many_share;
            for(k=0;k<sharers;k++)
            {
                if(expense[i].who_paid->usr_id==usrid && expense[i].who_share[k]->usr_id==usrid)          //checking userid matches any expense or not
                {    
                    flag=1;
                } 
            }                         
        }
        else
            i++;
    }
    if(flag==0)
    {
        printf("\nEnter correct expense id associated to your user id!\n ");
        delete_exp(usrid);
    }
    //deleting expense
    else
    {
        printf("Deleting Expense ID....\n");
        for(j=i;j<limit;j++)                                        //entries shifted
        {
            expense[j]=expense[j+1];
        }
        expense[limit-1].exp_id=0;                                   //last entry cleared
        expense[limit-1].exp_amt=0;
        expense[limit-1].who_paid='\0';
        expense[limit-1].how_many_share=0;
        for(int k=0;k<4;k++)
            expense[limit-1].who_share[k]='\0';
        printf("\nExpense Id deleted sucessfully!  :)\n");
    }
    return 0;
}

//function to view amount owed
float view_amount_owed(int usrid)
{
    int i=0,j=0,limit,flag=0,flag2=1,sharers=0;
    float total_amt=0,amt_per_head=0;
    limit=exp_count+1;
    printf("\nFollowing user id's owe you the respective amounts:-\n");
    while(i<limit)
    {
        if(expense[i].who_paid->usr_id==usrid)
        {
            sharers=expense[i].how_many_share;
            amt_per_head=expense[i].exp_amt/sharers;
            while(j<sharers)
            {    
                if(expense[i].who_share[j]->usr_id!=usrid)
                {
                    total_amt=total_amt+amt_per_head;
                    printf("User Id:%d\tUser Name: %s\tAmount Owed: %.2f\tExpense Id :%d\n",expense[i].who_share[j]->usr_id,expense[i].who_share[j]->usr_name,amt_per_head,expense[i].exp_id);
                }
                j++;
            }
            i++;   
        }
        else
            i++;
    }
    printf("\nThe amount that other users owe you is %0.2f Rs/-\n",total_amt);
    return total_amt;
}

//function to view amount to be paid
float view_amount_to_pay(int usrid)
{
    int i=0,j=0,limit,flag=0,flag2=1,sharers;
    float total_amt=0,amt_per_head=0;
    limit=exp_count+1;

    printf("\nYou owe the following user ids the respective amounts:-\n");
    while(i<limit)
    {
       if(expense[i].who_paid->usr_id!=usrid)                                            //you didnt psy
       {
            sharers=expense[i].how_many_share;
            for(int k=0;k<sharers;k++)
            {
                amt_per_head=expense[i].exp_amt/sharers;
                if(expense[i].who_share[k]->usr_id==usrid)                               //you shared
                {
                    total_amt+=amt_per_head;
                    printf("\nUser Id: %d\tUser Name: %s\tAmount to Pay: %.2f\tExpense Id :%d\n",expense[i].who_share[k]->usr_id,expense[i].who_share[k]->usr_name,amt_per_head,expense[i].exp_id);
                }
            }
            i++;
       }
       else
        i++;
    }  
    printf("\nTotal amount to be paid to other users is %0.2f Rs/-\n",total_amt);
    return total_amt;                        
}

//function to settle expenses
int settle_up(int usr_id1,int usr_id2)
{
    //usr_id1 is payer and usr_id2 is reciever
    int i=0,count,flag=0,how_many_share,k=0,settleid=0,flag2=0,exit=1,sharing_index;
    float amt_per_head=0;
    while(i<=exp_count)
    {
        if(expense[i].who_paid->usr_id==usr_id2)
        {
            how_many_share=expense[i].how_many_share;
           for(int j=0;j<how_many_share && flag==0;j++)
           {
                if(expense[i].who_share[j]->usr_id==usr_id1)
                {
                    flag=1;
                    amt_per_head=expense[i].exp_amt/how_many_share;
                    printf("\nYou owe user id:%d amount:%0.2f Rs/- with expense id:%d\n",usr_id1,amt_per_head,expense[i].exp_id);
                }
           } 
        }
        else
            i++;
    }
    while(i<=exp_count && flag2==0)
    {
        printf("\nEnter the expense id you want to settle:");
        scanf("%d",&settleid);
        if(expense[i].exp_id==settleid && expense[i].who_paid->usr_id==usr_id2)
        {
            how_many_share=expense[i].how_many_share;
            for(int j=0;j<how_many_share && flag2==0;j++)
           {
                if(expense[i].who_share[j]->usr_id==usr_id1)
                {
                    flag2=1;
                    sharing_index=j;                                  //index at which sharers exp id is at
                    amt_per_head=expense[i].exp_amt/how_many_share;
                    expense[i].exp_amt-=amt_per_head;
                }
           } 
        }
        else
            i++;
        if(flag2==1)
        {    
            printf("\nExpense settled!!\n");
            for(int j=sharing_index;j<how_many_share-1;j++)
            {
                expense[i].who_share[j]->usr_id=expense[i].who_share[j+1]->usr_id;
            }
            expense[i].how_many_share--;
            expense[i].who_paid->amt_spent-=amt_per_head;
        }
        else
        {
            printf("\n(Enter 0 to exit or any other no. to continue!)\n");
            scanf("%d",&exit);
            if(exit==1)
                flag2=1;
        }
    }
    return 0;
}

//function to display user balances
int user_balances()
{
    int i;
    float amt=0,t_amt_pay=0,t_amt_owed=0;
    for(i=0;i<usr_count+1;i++)
    {
        amt=view_amount_to_pay(user[i].usr_id);
        t_amt_pay+=amt;
    }
    printf("\nThe total amount to be paid by you to other users is %0.2f Rs/-\n",t_amt_pay);
    for(i=0;i<usr_count+1;i++)
    {
        amt=view_amount_owed(user[i].usr_id);
        t_amt_owed+=amt;
    }
    printf("The total amount to be paid by you to other users is %0.2f Rs/- \n",t_amt_owed);
    if(t_amt_pay>=t_amt_owed)
        printf("Net amount to be paid is %0.2f Rs/-\n",t_amt_pay-t_amt_owed);
    else 
        printf("Net amount to be recieved is %0.2f Rs/-\n",t_amt_owed-t_amt_pay);
    return 0;
}

//function to delete user id
int delete_usr_id(int usrid,int index)
{
    int expid,flag=0,i=0,j,limit1,limit2,sharers=0;
    float check1=0,check2=0;
    limit1=exp_count+1;
    limit2=usr_count+1;
    for(i=0;i<limit1 && flag==0;i++)
    {
        sharers=expense[i].how_many_share;
        for(j=0;j<sharers;j++)
        {
            if(expense[i].who_share[j]->usr_id==usrid || expense[i].who_paid->usr_id==usrid)
            {    
                flag=1; 
            } 
        }                         
    }
    if(flag==1)
    {
        printf("\n(Some pending expenses found!!)\n");
        check1=view_amount_owed(usrid);                              //shows pending settlements
        check2=view_amount_to_pay(usrid);
    }
    //deleting user id
    if(check1==0 && check2==0)
    {
        for(j=index;j<limit2;j++)                                         //shifting entries 
        {
            user[j]=user[j+1];
        }
        user[limit2-1].usr_id=0;                                      //last entry cleared
        user[limit2-1].amt_spent=0;
        for(int k=0;k<30;k++)
            user[limit2-1].usr_name[k]='\0';
        printf("\nUser Id deleted successfully :)\n");
    }
    else
        printf("First Settle up pending expenses!!\n");
    return 0;
}

//main function
int main()
{
    int i=0,usrid,k=-1,j=0,usrid2;

    printf("\nWelcome to your personalised expense application :)\n\n");
    while(i!=3)
    {
        printf("Enter\n 1:LOGIN\n 2:SIGN IN(NEW USER)\n 3:EXIT\n");
        scanf("%d",&i);
        if(i==1)
        {
            while(i==1)
            {
                printf("Enter your valid user id: ");
                scanf("%d",&usrid); 
                k = valid_usr_id(usrid)+1;                   
                if(k)
                    i=0;
            }
            //after login
            printf("\nSuccessful Login! :)\n");
            while(j!=8)
            {
                printf("\nEnter\n 1:ADD EXPENSES \n 2:DELETE EXPENSE\n 3:DELETE USER ID\n 4:VIEW AMOUNT OWED\n 5:VIEW AMOUNT TO PAY\n 6:SETTLE UP EXPENSES\n 7:SEE BALANCES\n 8:EXIT\n");
                scanf("%d",&j);
                if(j==1)
                {
                    add_expense(exp_count);                                     
                    exp_count++;
                }
                else if(j==2)
                {
                    delete_exp(usrid);
                    exp_count--;                                                 
                }
                else if(j==3)
                {
                    delete_usr_id(usrid,k-1);                                   //?
                    usr_count--;                                                 
                }
                else if(j==4)
                {
                    view_amount_owed(usrid);                                      //?
                }
                 else if(j==5)
                {
                    view_amount_to_pay(usrid);                                    //?
                }
                else if(j==6)
                {
                    printf("\nEnter user id to settle with: \n");
                    scanf("%d",&usrid2);
                    k=valid_usr_id(usrid2);
                    if(k)
                        settle_up(usrid,usrid2);                                  //?
                    else
                        printf("\nEnter valid user id to settle with!!\n");
                }
                else if(j==7)
                {
                    user_balances();                                                //?
                }
                else if(j==8)
                    printf("\nTHANK YOU!!  :)\n");
                else
                    printf("Invalid Input!!");
            }
        }
        else if(i==2)
        {
            add_user(usr_count);                                      
            usr_count++;                                                  
            printf("\nLogin as New User now!\n");                               
        }
        else if(i==3)
            printf("\nTHANK YOU!!  :)\n");
        else
            printf("Invalid Input!!\n");
    }
    return 0;
}
