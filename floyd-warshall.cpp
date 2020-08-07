
for(int i=0;i<n;i++)
{
	for(int j=0;j<n;j++)
	{
		for(int k=0;k<n;k++)
		{
			int v=distance[j][i]+distance[i][k];
			if(v<distance[j][k])
			{
				distance[j][k]=v;
			}
		}
	}
}
