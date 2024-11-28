import pandas as pd
import csv

input_file = 'output.csv'
output_file = 'output.txt'
selected_columns_names = ['date', 'deadline','country' ,'artist_genres']



df = pd.read_csv(input_file)
selected_columns = df[selected_columns_names].copy()

for column_name in selected_columns_names:
    #generating unique value for date and artist_genres
    if column_name == 'date' or column_name=='artist_genres':
        selected_columns[column_name] = pd.factorize(selected_columns[column_name])[0]
#Rearranging the columns as per required by the program
selected_columns['arrival_time'] = selected_columns['date']
selected_columns['leaf_computation_spot'] = selected_columns['country']
selected_columns['service_type'] = selected_columns['artist_genres']

selected_columns = selected_columns[['arrival_time', 'deadline', 'leaf_computation_spot', 'service_type']]
#printing the 400000 records
selected_columns.head(400000).to_csv(output_file, index=False, header=False, sep=' ', quoting=csv.QUOTE_NONE, escapechar=' ')

with open(output_file, 'r') as file:
    content = file.read()
    content = content.replace(',', ' ')

with open(output_file, 'w') as file:
    file.write(content)   
print(f"Selected columns have been written to {output_file}.")
