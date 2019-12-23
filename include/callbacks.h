#ifndef ULFIUS_CALLBACKS_H
#define ULFIUS_CALLBACKS_H

int callback_api (const struct _u_request * request, struct _u_response * response, void * user_data);
int callback_not_found (const struct _u_request * request, struct _u_response * response, void * user_data);

#endif //ULFIUS_CALLBACKS_H
