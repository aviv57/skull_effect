from fastapi import FastAPI, Response
from pydantic import BaseModel
import asyncio

class SetEventBody(BaseModel):
    event_body: dict

SET_EVENT_PASSWORD = ''

app = FastAPI(docs_url=None, redoc_url=None, openapi_url=None)
g_event = asyncio.Event()


@app.post("/set_event")
async def set_event(event_body: SetEventBody):
    event_body = event_body.event_body
    if event_body.get('password') == SET_EVENT_PASSWORD:
        g_event.set()
    return Response()

@app.get("/wait_for_event")
async def wait_for_event():
    try:
        was_event_set = await asyncio.wait_for(g_event.wait(), timeout=15.0)
    except asyncio.exceptions.TimeoutError:
        was_event_set = False
    if was_event_set:
        g_event.clear()

    return {"was_event_set": was_event_set}